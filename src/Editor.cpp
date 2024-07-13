//
// Created by Madhav Shekhar Sharma on 7/12/24.
//

#include "Editor.h"
#include <iostream>

Editor::Editor() : buffer(std::make_unique<Buffer>()), terminal(std::make_unique<Terminal>()) {
}
void Editor::Run() {
  while (running) {
	terminal->Render(*buffer);
	DrawStatusBar();
	auto [cursorRow, cursorCol] = buffer->GetCursorPosition();
	terminal->MoveCursor(cursorCol, cursorRow);
	int key = terminal->ReadKey();
	ProcessKey(key);
  }
}
void Editor::ProcessKey(int key) {
  std::cerr << "Keypress: " << key << " in mode: " << (mode == Mode::Normal ? "Normal" : "Insert") << std::endl;
  if (mode == Mode::Insert)
	HandleInsertMode(key);
  else
	HandleNormalMode(key);
}
void Editor::HandleNormalMode(int key) {
  switch (key) {
	case 'q': running = false; break;
	case 'i': mode = Mode::Insert; break;
	case Terminal::KEY_DOWN:
	case 'j': buffer->MoveCursor(0, 1); break;
	case Terminal::KEY_UP:
	case 'k': buffer->MoveCursor(0, -1); break;
	case Terminal::KEY_LEFT:
	case 'h': buffer->MoveCursor(-1, 0); break;
	case Terminal::KEY_RIGHT:
	case 'l': buffer->MoveCursor(1, 0); break;
	default: std::cout << "Unknown key: " << key << std::endl;
  }
}
void Editor::HandleInsertMode(int key) {
  if (key == Terminal::KEY_ESC)
	mode = Mode::Normal;
  else if (key == Terminal::KEY_BACKSPACE || key == 8) // backspace
	buffer->DeleteChar();
  else if (key == Terminal::KEY_ENTER)
	buffer->Insert('\n');
  else
	buffer->Insert(static_cast<char>(key));
}
void Editor::DrawStatusBar() {
  auto [rows, cols] = terminal->GetWindowSize();
  std::string modeStr = (mode == Mode::Normal) ? "-- NORMAL --" : "-- INSERT --";
  std::string status = modeStr + " " + std::to_string(buffer->GetNumLines()) + " lines" + " | " + "press 'q' to quit";
  terminal->DrawStatusBar(status, rows - 1);
}
