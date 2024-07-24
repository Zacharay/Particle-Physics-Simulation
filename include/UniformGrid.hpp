#pragma once
#include <vector>
#include "Globals.hpp"

struct GridCell {
	std::vector<unsigned int>objects;
};

class UniformGrid {
	float cellSize;

	int numOfCols;
	int numOfCells;
	int numOfRows;

	std::vector<GridCell>cells;


	int getCellID(unsigned int row, unsigned int col);
public:

	UniformGrid(float cellSize);
	void clearGrid();
	void addItem(float posX, float posY, unsigned int objID);
	void getNeighbours(unsigned int cellID,std::vector<unsigned int>&nbr)const ;
	std::vector<unsigned int> getCellItems(unsigned int cellID)const ;
	unsigned int getNumOfCells()const;
};