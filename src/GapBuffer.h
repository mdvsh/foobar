//
// Created by Madhav Shekhar Sharma on 7/12/24.
//

#ifndef FOOBAR_SRC_GAPBUFFER_H_
#define FOOBAR_SRC_GAPBUFFER_H_

#include <vector>
#include <string>

const size_t GAP_SIZE = 128;
const size_t GROWTH_FIXED_SIZE = 1024;

class GapBuffer {
 private:
  std::vector<char> buffer;
  size_t gapStart;
  size_t gapEnd;

  void MoveGap(size_t pos);
  void GrowGap();

 public:
  GapBuffer();
  void Insert(size_t pos, char ch);
  void Insert(size_t pos, const std::string& str);
  void DeleteChar(size_t pos);
  void DeleteRange(size_t start, size_t end);
  [[nodiscard]] char At(size_t pos) const;
  [[nodiscard]] std::string Substr(size_t start, size_t end) const;
  [[nodiscard]] size_t Size() const;
  [[nodiscard]] std::string ToString() const;
};

#endif//FOOBAR_SRC_GAPBUFFER_H_
