//
// Created by Madhav Shekhar Sharma on 7/12/24.
//

#include "Terminal.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

Terminal::Terminal() {
  EnableRawMode();
}
Terminal::~Terminal() {
  DisableRawMode();
}
void Terminal::Render(const Buffer &buffer) {
  ClearScreen();
  auto [rows, cols] = GetWindowSize();
  auto lines = buffer.GetLines(0, rows - 1);
  for (size_t i = 0; i < lines.size(); ++i) {
	MoveCursor(0, i);
	std::cout << lines[i] << "\r\n";
  }

  auto [cursorRow, cursorCol] = buffer.GetCursorPosition();
  MoveCursor(cursorCol, cursorRow);
  std::cout.flush();
}

//void Terminal::Render(const Buffer& buffer) {
//  auto [rows, cols] = GetWindowSize();
//  auto lines = buffer.GetLines(0, rows);
//  auto [cursor_row, cursor_col] = buffer.GetCursorPosition();
//
//  lastRenderedBuffer.resize(rows);
//
//  for (size_t i = 0; i < lines.size(); ++i) {
//	if (i >= lastRenderedBuffer.size() || lines[i] != lastRenderedBuffer[i]) {
//	  UpdateLine(i, lines[i]);
//	  lastRenderedBuffer[i] = lines[i];
//	}
//  }
//
//  // lear any remaining lines if the buffer is now shorter
//  for (size_t i = lines.size(); i < lastRenderedBuffer.size(); ++i) {
//	UpdateLine(i, "");
//	lastRenderedBuffer[i] = "";
//  }
//
//  // update cursor position if changed
//  if (std::make_pair(cursor_row, cursor_col) != lastCursorPosition) {
//	MoveCursor(cursor_col, cursor_row);
//	lastCursorPosition = {cursor_row, cursor_col};
//  }
//
//  std::cout << std::flush;
//}

void Terminal::UpdateLine(size_t row, const std::string &line) {
  MoveCursor(0, row);
  std::cout << "\x1b[K";
  std::cout << line;
}

int Terminal::ReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
	if (nread == -1 && errno != EAGAIN) return -1;
  }
  if (c == '\x1b') {
	char seq[3];
	if (read(STDIN_FILENO, &seq[0], 1) != 1) return KEY_ESC;
	if (read(STDIN_FILENO, &seq[1], 1) != 1) return KEY_ESC;
	if (seq[0] == '[') {
	  switch (seq[1]) {
		case 'A': return KEY_UP;
		case 'B': return KEY_DOWN;
		case 'C': return KEY_RIGHT;
		case 'D': return KEY_LEFT;
	  }
	}
	return KEY_ESC;
  } else if (c == 127) {
	return KEY_BACKSPACE;
  } else if (c == 13) {
	return KEY_ENTER;
  } else {
	return c;
  }
}
std::pair<size_t, size_t> Terminal::GetWindowSize() const {
  struct winsize ws {};
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
	return {24, 80};// default, later paramtr
  }
  return {ws.ws_row, ws.ws_col};
}
void Terminal::EnableRawMode() {
  tcgetattr(STDIN_FILENO, &_termios);
  struct termios raw = _termios;
  raw.c_iflag &= ~(ICRNL | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void Terminal::DisableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &_termios);
}
void Terminal::ClearScreen() {
  std::cout << "\x1b[2J\x1b[H" << std::flush;
  // escape, clear, escape, home
}
void Terminal::MoveCursor(int x, int y) {
  std::cout << "\x1b[" << y << ";" << x << "H";
  // escape, y, ;, x, H
}
void Terminal::DrawStatusBar(const std::string &status, size_t row) const {
  MoveCursor(0, row);
  std::cout << "\x1b[7m" << status << std::string(GetWindowSize().second - status.length(), ' ') << "\x1b[m";
  std::cout.flush();
}
