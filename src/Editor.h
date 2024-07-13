//
// Created by Madhav Shekhar Sharma on 7/12/24.
//

#ifndef FOOBAR_SRC_EDITOR_H_
#define FOOBAR_SRC_EDITOR_H_

#include "Buffer.h"
#include "Terminal.h"
#include <string>
#include <memory>

class Editor {
 public:
  Editor();
  void Run();

  enum class Mode { Normal, Insert };
 private:
  std::unique_ptr<Buffer> buffer;
  std::unique_ptr<Terminal> terminal;
  bool running = true;

  void ProcessKey(int key);
  void HandleNormalMode(int key);
  void HandleInsertMode(int key);
  void DrawStatusBar();
  Mode mode = Mode::Normal;
};

#endif//FOOBAR_SRC_EDITOR_H_
