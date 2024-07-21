#include "UniformGrid.hpp"
#include <iostream>
unsigned int UniformGrid::getCellID(unsigned int row, unsigned int col)
{
	return this->numCols * row  + col;
}


UniformGrid::UniformGrid()
{

	this->cellSize = 200.0f;
	this->numRows = WINDOW_HEIGHT / cellSize;
	this->numCols = WINDOW_WIDTH / cellSize;
	this->numOfCells = numRows * numCols;
	cells.resize(numOfCells);


	cells[0].push_back(2);
	cells[0].push_back(3);
	cells[0].push_back(4);
	cells[1].push_back(7);
	cells[2].push_back(8);

	for (std::vector<unsigned int>cell : cells)
	{
		for (unsigned int cellItem : cell)
		{
			std::cout << cellItem << " ";
		}
		
	}
	std::cout << std::endl;
	this->clearGrid();
}

void UniformGrid::clearGrid()
{

	for (std::vector<unsigned int>& cell : cells)
	{
		cell.clear();
	}

	for (std::vector<unsigned int>cell : cells)
	{
		for (unsigned int cellItem : cell)
		{
			std::cout << cellItem << " ";
		}

	}
	std::cout << std::endl;
}

void UniformGrid::addItem(float posX, float posY, unsigned int objID)
{
	unsigned int col = static_cast<unsigned int>(posX / this->cellSize);
	unsigned int row = this->numRows-1-static_cast<unsigned int>(posY / this->cellSize);

	

	unsigned int cellID = this->getCellID(row, col);

	this->cells[cellID].push_back(objID);
}
