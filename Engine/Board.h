#pragma once
#include "Graphics.h"
#include "Location.h"


class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	Location GetGridLocation() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBackground();

private:
	static constexpr int dimension = 20;
	static constexpr Location boardLocation = {1,2};
	static constexpr int width = 25;
	static constexpr int height = 25;
	static constexpr Color backgroundColor = Colors::White;
	Graphics& gfx;


};

