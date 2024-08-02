#pragma once
#include <vector>
#include "Globals.hpp"

struct GridCell {
	std::vector<unsigned int>m_particles;
};

class UniformGrid {
	float m_cellSize;

	int m_numOfCols;
	int m_numOfCells;
	int m_numOfRows;

	std::vector<GridCell>m_cells;


	int getCellID(unsigned int row, unsigned int col);
public:

	UniformGrid(float cellSize);
	void clearGrid();
	void addItem(float posX, float posY, unsigned int objID);
	void getNeighbours(unsigned int cellID,std::vector<unsigned int>&nbr)const ;
	std::vector<unsigned int> getCellItems(unsigned int cellID)const ;
	unsigned int getNumOfCells()const;
};