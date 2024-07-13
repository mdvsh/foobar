//
// Created by Madhav Shekhar Sharma on 7/12/24.
//

#include "GapBuffer.h"
#include <algorithm>

GapBuffer::GapBuffer() : gapStart(0), gapEnd(GAP_SIZE) {
  buffer.resize(GAP_SIZE, '\0');
}
void GapBuffer::MoveGap(size_t pos) {
  if (pos == gapStart) return;
  if (pos < gapStart) {
	std::copy_backward(buffer.begin() + pos, buffer.begin() + gapStart, buffer.begin() + gapEnd);
	const size_t dist = gapStart - pos;
	gapStart -= dist;
	gapEnd -= dist;
  } else {
	const size_t dist = pos - gapStart;
	std::copy(buffer.begin() + gapEnd, buffer.begin() + gapEnd + dist, buffer.begin() + gapStart);
	gapStart += dist;
	gapEnd += dist;
  }
}
void GapBuffer::GrowGap() {
  const size_t newGapSize = std::max(GROWTH_FIXED_SIZE, buffer.size() / 2);
  buffer.insert(buffer.begin() + gapEnd, newGapSize, '\0');
  gapEnd += newGapSize;
}

void GapBuffer::Insert(size_t pos, char ch) {
  MoveGap(pos);
  if (gapStart == gapEnd) GrowGap();
  buffer[gapStart++] = ch;
}
void GapBuffer::Insert(size_t pos, const std::string &str) {
  MoveGap(pos);
  if (gapEnd - gapStart < str.size()) GrowGap();
  std::copy(str.begin(), str.end(), buffer.begin() + gapStart);
  gapStart += str.size();
}
void GapBuffer::DeleteChar(size_t pos) {
  if (pos >= gapStart) pos += gapEnd - gapStart;// get actual pos
  if (pos == gapStart - 1) --gapStart;
  else {
	MoveGap(pos + 1);
	--gapStart;
  }
}
void GapBuffer::DeleteRange(size_t start, size_t end) {
  MoveGap(start);// eat range elems with gap
  gapEnd += end - start;
}
char GapBuffer::At(size_t pos) const {
  if (pos >= gapStart) pos += gapEnd - gapStart;
  return buffer[pos];
}
std::string GapBuffer::Substr(size_t start, size_t end) const {
  std::string res;
  res.reserve(end - start);
  for (size_t i = start; i < end; ++i)
	res.push_back(At(i));
  return res;
}
size_t GapBuffer::Size() const {
  return buffer.size() - (gapEnd - gapStart);
}
std::string GapBuffer::ToString() const {
  std::string res;
  res.reserve(Size());
  for (size_t i = 0; i < gapStart; ++i)
	res.push_back(buffer[i]);
  for (size_t i = gapEnd; i < buffer.size(); ++i)
	res.push_back(buffer[i]);
  return res;
}
