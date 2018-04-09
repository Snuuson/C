#include "Snake.h"
#include <assert.h>
#include "Board.h"
#include <random>
Snake::Snake(const Location & loc)
	:
	rng(std::random_device()())
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc); 
}

Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax) {
		segments[nSegments].Follow(segments[nSegments - 1]);
		segments[nSegments].InitBody();
		nSegments++;

	}
}

void Snake::Draw(Board & brd)
{	
	
	for (int i = 0; i < nSegments; i++) {
		if (rainbow) 
		{
			segments[i].randomColor(rng);
		}
		else {
			if (i == 0) {
				segments[i].setColor(Snake::headColor);
			}
			else {
				segments[i].setColor(Snake::bodyColor);
			}
		}
		segments[i].Draw(brd);
	}
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody()
{
	
	c = Snake::bodyColor;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board& brd) 
{
	brd.DrawCell(loc,c);
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	//assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}

void Snake::Segment::randomColor(std::mt19937 & rng)
{
	std::uniform_int_distribution<int> red(0, 255);
	std::uniform_int_distribution<int> green(0, 255);
	std::uniform_int_distribution<int> blue(0, 255);
	c = Color(red(rng), green(rng), blue(rng));


}

void Snake::Segment::setColor(Color color)
{
	c = color;
}

bool Snake::IsInTileExceptEnd(const Location & target) const
{
	for (int i = 0; i < nSegments -1; i++) {
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile(const Location & target) const
{
	for (int i = 0; i < nSegments; i++) {
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}

void Snake::SnakeReset()
{
	nSegments = 1;
	segments[0].InitHead({ 2,2 });
}


