#pragma once
#include "Board.h"
#include <random>
class Snake
{
public :
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_loc) const;
	void Grow();
	void Draw(Board& brd);
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
	void SnakeReset();
	bool rainbow = false;
	std::mt19937 rng;
	int rainbowCounter = 0;
	int inputLockCounter = 0;
	bool inputLocked = false;
	class Segment {
	public: 
		void InitHead(const Location& in_loc);
		void InitBody();
		void Follow(const Segment& next);
		void Draw(Board& brd);
		void MoveBy(const Location& delta_loc);
		const Location& GetLocation() const;
		void randomColor(std::mt19937 & rng);
		void setColor(Color color);
		

		
	private:
		Location loc;
		Color c;

	};
private:
	static constexpr Color headColor = Color(255,114,159);
	static constexpr Color bodyColor = Color(86, 203, 249);
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
	
};



