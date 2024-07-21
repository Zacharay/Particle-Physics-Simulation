#pragma once
#include <vector>
#include "Globals.hpp"
class UniformGrid {
	unsigned int cellSize;
	unsigned int numRows;
	unsigned int numCols;
	unsigned int numOfCells;

	std::vector<std::vector<unsigned int>>cells;


	unsigned int getCellID(unsigned int row, unsigned int col);
public:

	UniformGrid();
	void clearGrid();
	void addItem(float posX,float posY,unsigned int objID);
	std::vector<unsigned int> getNeighbors();
};