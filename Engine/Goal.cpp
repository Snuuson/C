#include "Goal.h"




Goal::Goal(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	
	Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	Goal::counter++;
	if ((Goal::counter+1) % 3 == 0) {
		c = Colors::Yellow;
	}
	else {
		c = Color(38, 84, 124);
	}
	if (Goal::counter%3 == 0) {
		rainbow = true;
		
	}
	
	std::uniform_int_distribution<int> xDist(brd.GetGridLocation().x, brd.GetGridWidth() + brd.GetGridLocation().x - 1);
	std::uniform_int_distribution<int> yDist(brd.GetGridLocation().y, brd.GetGridHeight() + brd.GetGridLocation().y - 1);
	Location newLoc;
	do 
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc));

	loc = newLoc;
	
		
	
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location & Goal::GetLocation() const
{
	return loc;
}
