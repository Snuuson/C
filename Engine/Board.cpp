#include "Board.h"
#include "Graphics.h"
#include <assert.h>


Board::Board(Graphics & gfx)
	:
	gfx(gfx)

{
}

void Board::DrawCellSpecial(const Location& loc, Color c)
{
	assert(loc.x >= boardLocation.x);
	assert(loc.x < width + boardLocation.x);

	assert(loc.y >= boardLocation.y);
	assert(loc.y < height + boardLocation.y);
	
	gfx.DrawRectSpecialDim(loc.x * dimension, loc.y * dimension, dimension, dimension, c);

	

}
void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= boardLocation.x);
	assert(loc.x < width + boardLocation.x);

	assert(loc.y >= boardLocation.y);
	assert(loc.y < height + boardLocation.y);

	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension, c);



}


int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

Location Board::GetGridLocation() const
{
	return boardLocation;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= boardLocation.x && loc.x < width + boardLocation.x && loc.y >= boardLocation.y && loc.y < height + boardLocation.y;
}

void Board::DrawBackground()
{
	
	for (int y = boardLocation.y ; y < height + boardLocation.y; y++) {
		for (int x = boardLocation.x; x  < width + boardLocation.x; x++) {
			Location l = { x,y };
			DrawCell(l, Board::backgroundColor);
		}
	}
}
