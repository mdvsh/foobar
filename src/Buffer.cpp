//
// Created by Madhav Shekhar Sharma on 7/12/24.
//

#include "Buffer.h"
Buffer::Buffer() : cursorRow(0), cursorCol(0) {
  lineStarts.push_back(0);
}
void Buffer::Insert(char ch) {
  size_t pos = GetPosition(cursorRow, cursorCol);
  content.Insert(pos, ch);
  if (ch == '\n') {
	cursorRow++;
	cursorCol = 0;
  } else {
	cursorCol++;
  }
  UpdateLineStarts();
}
void Buffer::DeleteChar() {
  if (cursorRow > 0 || cursorCol > 0) {
	size_t pos = GetPosition(cursorRow, cursorCol);
	if (cursorCol == 0) {
	  cursorRow--;
	  cursorCol = lineStarts[cursorRow + 1] - lineStarts[cursorRow] - 1;
	} else
	  cursorCol--;
	content.DeleteChar(pos - 1);
	UpdateLineStarts();
  }
}
void Buffer::MoveCursor(int dx, int dy) {
  int nextRow = std::max(0, std::min(static_cast<int>(cursorRow) + dy, static_cast<int>(GetNumLines() - 1)));
  int nextCol = std::max(0, std::min(static_cast<int>(cursorCol) + dx, static_cast<int>(lineStarts[nextRow + 1] - lineStarts[nextRow] - 1)));

  cursorRow = nextRow;
  cursorCol = nextCol;
}
std::string Buffer::GetCurrentLine() const {
  size_t end = (cursorRow + 1 < lineStarts.size()) ? lineStarts[cursorRow + 1] : content.Size();
  return content.Substr(lineStarts[cursorRow], end);
}
std::vector<std::string> Buffer::GetLines(size_t start, size_t end) const {
  std::vector<std::string> lines;
  for (size_t i = start; i < std::min(end, GetNumLines()); ++i) {
	size_t lineEnd = (i + 1 < lineStarts.size()) ? lineStarts[i + 1] : content.Size();
	lines.push_back(content.Substr(lineStarts[i], lineEnd));
  }
  return lines;
}
std::pair<size_t, size_t> Buffer::GetCursorPosition() const {
  return {cursorRow, cursorCol};
}
size_t Buffer::GetNumLines() const {
  return lineStarts.size();
}
void Buffer::UpdateLineStarts() {
  // todo: optimize
  lineStarts.clear();
  lineStarts.push_back(0);
  for (size_t i = 0; i < content.Size(); ++i) {
	if (content.At(i) == '\n') {
	  lineStarts.push_back(i + 1);
	}
  }
}
size_t Buffer::GetPosition(size_t row, size_t col) const {
  return lineStarts[row] + col;
}
