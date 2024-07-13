#include "Editor.h"
#include "Terminal.h"
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "Launching foo-bar text editor" << std::endl;
  try {
	Editor editor;
	editor.Run();
  } catch (const std::exception &e) {
	std::cerr << "An error occurred: " << e.what() << std::endl;
	return 1;
  }
  return 0;
}