#include "UniformGrid.hpp"
#include "UniformGrid.hpp"
#include <iostream>
int UniformGrid::getCellID(unsigned int row, unsigned int col)
{
	return this->numOfCols * row  + col;
}


UniformGrid::UniformGrid(float cellSize)
{

	this->cellSize = cellSize;
	this->numOfCols = static_cast<int>(SIMULATION_WIDTH / cellSize);
	this->numOfRows = this->numOfCols;
	this->numOfCells = this->numOfCols * this->numOfCols;


	this->cells.resize(this->numOfCells);
	
	this->clearGrid();
}

void UniformGrid::clearGrid()
{

	for (GridCell &cell : this->cells)
	{
		cell.objects.clear();
	}

}

void UniformGrid::addItem(float posX, float posY, unsigned int objID)
{
	unsigned int col = static_cast<unsigned int>(posX / this->cellSize);
	unsigned int row = this->numOfRows-1-static_cast<unsigned int>(posY / this->cellSize);

	unsigned int cellID = this->getCellID(row, col);

	this->cells[cellID].objects.push_back(objID);
}

std::vector<unsigned int> UniformGrid::getCellItems(unsigned int cellID)const 
{
	return this->cells[cellID].objects;
}

unsigned int UniformGrid::getNumOfCells() const
{
	return this->numOfCells;
}

void UniformGrid::getNeighbours(unsigned int cellID,std::vector<unsigned int> &nbr)const
{
	
	
	bool isLeftMostCell = cellID % this->numOfCols == 0;
	bool isRightMostCell = (cellID+1) % this->numOfCols == 0;
	bool isTopMostCell = cellID < this->numOfCols;
	bool isBottomMostCell = this->numOfCols *(this->numOfCols -1) <= cellID;
	
	

	std::vector<int> moveDirections;

	if (!isTopMostCell)
	{
		moveDirections.push_back(-this->numOfCols);

		//left diagonal
		if (!isLeftMostCell)
		{
			moveDirections.push_back(-(this->numOfCols +1));
		}
		//right diagonal
		if (!isRightMostCell)
		{
			moveDirections.push_back(-(this->numOfCols - 1));
		}
	}
	if (!isBottomMostCell)
	{
		moveDirections.push_back(this->numOfCols);
		//left diagonal
		if (!isLeftMostCell)
		{
			moveDirections.push_back((this->numOfCols - 1));
		}
		//right diagonal
		if (!isRightMostCell)
		{
			moveDirections.push_back((this->numOfCols + 1));
		}
	}

	if (!isLeftMostCell)moveDirections.push_back(-1);
	if (!isRightMostCell)
	{

		moveDirections.push_back(1);
	}


	for (auto direction : moveDirections)
	{
		int newCellID = cellID + direction;

		for (auto elementID : this->cells[newCellID].objects)
		{
			nbr.push_back(elementID);
		}
	}
}