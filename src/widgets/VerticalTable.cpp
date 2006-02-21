#include "VerticalTable.hpp"

VerticalTable::VerticalTable(Screen& screen) : Window(screen), 
					       columns_(0), rows_(0),
					       activeRow_(0),
					       activeStyle_(0) {}
	
void VerticalTable::setColumns(unsigned columns) {
    cells_.resize(columns * rows_);
    columns_ = columns;
}

unsigned VerticalTable::getColumns() const {
    return columns_;
}

unsigned VerticalTable::getRows() const {
    return rows_;
}

void VerticalTable::setRows(unsigned rows) {
    cells_.resize(columns_ * rows);
    rows_ = rows;
}

void VerticalTable::setActiveRow(unsigned row) {
    activeRow_ = row;
}

unsigned VerticalTable::getActiveRow() const {
    return activeRow_;
}

void VerticalTable::setText(unsigned column, unsigned row, 
	const std::string& text) {
    cells_[column * rows_ + row].text = text;
}

void VerticalTable::setStyle(unsigned column, unsigned row, int style) {
    cells_[column * rows_ + row].style = style;
}

void VerticalTable::setActiveStyle(int style) {
    activeStyle_ = style;
}

void VerticalTable::update() const {
    clear();

    for (unsigned row = 0; row < rows_; ++row) {
	unsigned y = row;
	for (unsigned column = 0; column < columns_; ++column) {
	    unsigned x = getWidth() * column / columns_;
	    int style;
	    if (row == activeRow_) style = activeStyle_;
	    else style = cells_[column * rows_ + row].style;
	    Window::setStyle(style);
	    putString(x, y, cells_[column * rows_ + row].text);
	}
    }

    Window::update();
}
