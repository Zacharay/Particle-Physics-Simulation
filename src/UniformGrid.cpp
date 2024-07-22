#include "UniformGrid.hpp"
#include "UniformGrid.hpp"
#include <iostream>
unsigned int UniformGrid::getCellID(unsigned int row, unsigned int col)
{
	return this->numCols * row  + col;
}


UniformGrid::UniformGrid(float cellSize)
{

	this->cellSize = cellSize;
	this->numRows = WINDOW_HEIGHT / cellSize;
	this->numCols = WINDOW_WIDTH / cellSize;
	this->numOfCells = numRows * numCols;
	cells.resize(numOfCells);
	
	this->clearGrid();
}

void UniformGrid::clearGrid()
{

	for (std::vector<unsigned int>& cell : cells)
	{
		cell.clear();
	}

}

void UniformGrid::addItem(float posX, float posY, unsigned int objID)
{
	unsigned int col = static_cast<unsigned int>(posX / this->cellSize);
	unsigned int row = this->numRows-1-static_cast<unsigned int>(posY / this->cellSize);

	

	unsigned int cellID = this->getCellID(row, col);

	this->cells[cellID].push_back(objID);
}

std::vector<unsigned int> UniformGrid::getCellItems(unsigned int cellID)
{
	return this->cells[cellID];
}

unsigned int UniformGrid::getNumOfCells() const
{
	return this->numOfCells;
}

std::vector<unsigned int> UniformGrid::getNeighbours(unsigned int cellID)
{
	
	
	bool isLeftMostCell = cellID % this->numCols == 0;
	bool isRightMostCell = (cellID+1) % this->numCols == 0;
	bool isTopMostCell = cellID < this->numCols;
	bool isBottomMostCell = this->numCols*(this->numRows-1) <= cellID;
	
	

	std::vector<int> moveDirections;

	if (!isTopMostCell)
	{
		moveDirections.push_back(-this->numCols);

		//left diagonal
		if (!isLeftMostCell)
		{
			moveDirections.push_back(-(this->numCols+1));
		}
		//right diagonal
		if (!isRightMostCell)
		{
			moveDirections.push_back(-(this->numCols - 1));
		}
	}
	if (!isBottomMostCell)
	{
		moveDirections.push_back(this->numCols);
		//left diagonal
		if (!isLeftMostCell)
		{
			moveDirections.push_back((this->numCols - 1));
		}
		//right diagonal
		if (!isRightMostCell)
		{
			moveDirections.push_back((this->numCols + 1));
		}
	}

	if (!isLeftMostCell)moveDirections.push_back(-1);
	if (!isRightMostCell)
	{

		moveDirections.push_back(1);
	}

	std::vector<unsigned int>nbr;
	for (auto direction : moveDirections)
	{
		int newCellID = cellID + direction;

		for (auto elementID : this->cells[newCellID])
		{
			nbr.push_back(elementID);
		}
	}

	return nbr;
}
