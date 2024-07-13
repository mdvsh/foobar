//
// Created by Madhav Shekhar Sharma on 7/12/24.
//

#ifndef FOOBAR_SRC_BUFFER_H_
#define FOOBAR_SRC_BUFFER_H_

#include <vector>
#include <string>
#include "GapBuffer.h"

class Buffer {
 public:
  	Buffer();
	void Insert(char ch);
	void DeleteChar();
	void MoveCursor(int dx, int dy);
	std::string GetCurrentLine() const;
	std::vector<std::string> GetLines(size_t start, size_t end) const;
	std::pair<size_t, size_t> GetCursorPosition() const;
	size_t GetNumLines() const;

 private:
  	GapBuffer content;
	std::vector<size_t> lineStarts;
	size_t cursorRow;
	size_t cursorCol;

	void UpdateLineStarts();
	size_t GetPosition(size_t row, size_t col) const;
};

#endif//FOOBAR_SRC_BUFFER_H_
