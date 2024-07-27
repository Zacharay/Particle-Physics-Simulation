#include "UniformGrid.hpp"
#include "UniformGrid.hpp"
#include <iostream>
int UniformGrid::getCellID(unsigned int row, unsigned int col)
{
	return this->m_numOfCols * row  + col;
}


UniformGrid::UniformGrid(float cellSize)
{

	m_cellSize = cellSize;
	m_numOfCols = static_cast<int>(SIMULATION_WIDTH / cellSize);
	m_numOfRows = m_numOfCols;
	m_numOfCells = m_numOfCols * m_numOfCols;


	m_cells.resize(m_numOfCells);
	
	clearGrid();
}

void UniformGrid::clearGrid()
{

	for (GridCell &cell : this->m_cells)
	{
		cell.objects.clear();
	}

}

void UniformGrid::addItem(float posX, float posY, unsigned int objID)
{
	unsigned int col = static_cast<unsigned int>(posX / m_cellSize);
	unsigned int row =m_numOfRows-1-static_cast<unsigned int>(posY / m_cellSize);

	unsigned int cellID =getCellID(row, col);

	m_cells[cellID].objects.push_back(objID);
}

std::vector<unsigned int> UniformGrid::getCellItems(unsigned int cellID)const 
{
	return m_cells[cellID].objects;
}

unsigned int UniformGrid::getNumOfCells() const
{
	return m_numOfCells;
}

void UniformGrid::getNeighbours(unsigned int cellID,std::vector<unsigned int> &nbr)const
{
	
	
	bool isLeftMostCell = cellID % m_numOfCols == 0;
	bool isRightMostCell = (cellID+1) %m_numOfCols == 0;
	bool isTopMostCell = cellID < m_numOfCols;
	bool isBottomMostCell =m_numOfCols *(m_numOfCols -1) <= cellID;
	
	

	std::vector<int> moveDirections;
	moveDirections.reserve(8);
	if (!isTopMostCell)
	{
		moveDirections.push_back(-m_numOfCols);

		//left diagonal
		if (!isLeftMostCell)
		{
			moveDirections.push_back(-(m_numOfCols +1));
		}
		//right diagonal
		if (!isRightMostCell)
		{
			moveDirections.push_back(-(m_numOfCols - 1));
		}
	}
	if (!isBottomMostCell)
	{
		moveDirections.push_back(m_numOfCols);
		//left diagonal
		if (!isLeftMostCell)
		{
			moveDirections.push_back((m_numOfCols - 1));
		}
		//right diagonal
		if (!isRightMostCell)
		{
			moveDirections.push_back((m_numOfCols + 1));
		}
	}

	if (!isLeftMostCell)
		moveDirections.push_back(-1);
	if (!isRightMostCell)
		moveDirections.push_back(1);


	for (auto direction : moveDirections)
	{
		int newCellID = cellID + direction;

		for (auto elementID : this->m_cells[newCellID].objects)
		{
			nbr.push_back(elementID);
		}
	}
}