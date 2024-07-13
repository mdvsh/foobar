//
// Created by Madhav Shekhar Sharma on 7/12/24.
//

#ifndef FOOBAR_SRC_TERMINAL_H_
#define FOOBAR_SRC_TERMINAL_H_

#include "Buffer.h"
#include <termios.h>
#include <string>
#include <vector>

class Terminal {
 public:

	Terminal();
	~Terminal();

	static const int KEY_ESC = 27;
	static const int KEY_ENTER = 13;
	static const int KEY_BACKSPACE = 127;
	static const int KEY_UP = 1000;
	static const int KEY_DOWN = 1001;
	static const int KEY_LEFT = 1002;
	static const int KEY_RIGHT = 1003;

	void Render(const Buffer& buffer);
	static int ReadKey() ;
	[[nodiscard]] std::pair<size_t, size_t> GetWindowSize() const;
	void DrawStatusBar(const std::string& status, size_t row) const;
	static void MoveCursor(int x, int y) ;

   private:
	struct termios _termios{};
	std::vector<std::string> lastRenderedBuffer;
	std::pair<size_t, size_t> lastCursorPosition;
	void EnableRawMode();
	void DisableRawMode();
	static void ClearScreen() ;
	void UpdateLine(size_t row, const std::string& line);
};

#endif//FOOBAR_SRC_TERMINAL_H_
