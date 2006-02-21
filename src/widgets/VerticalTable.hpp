#ifndef CBM_WIDGETS_VERTICALTABLE_HPP
#define CBM_WIDGETS__HPP

#include "Window.hpp"
#include <string>
#include <vector>

class VerticalTable : public Window {
    public:
	VerticalTable(Screen& screen);
	
	void setColumns(unsigned columns);
	unsigned getColumns() const;
	
	void setRows(unsigned rows);
	unsigned getRows() const;
	
	void setActiveRow(unsigned row);
	unsigned getActiveRow() const;
	
	void setText(unsigned column, unsigned row, const std::string& text);
	void setStyle(unsigned column, unsigned row, int style);
	void setActiveStyle(int style);

    protected:	
	virtual void update() const;

    private:
	struct Cell {
	    Cell() : style(0) {}

	    std::string text;
	    int style;
	};
	unsigned columns_, rows_, activeRow_;
	int activeStyle_;
	std::vector<Cell> cells_;
};

#endif

