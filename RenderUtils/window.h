#pragma once

class Window
{
private:
	int width, height;
	char title[64];
	bool isInitialized = false;
	//forward declare
	struct GLFWwindow *winHandle = nullptr;

public:
	bool init(int a_width = 800, int a_height = 600, char *a_title = "Game Window"); // Setup, Start, Initialize... etc.
	bool step();                                         // Update, Refresh
	bool term();                                         // Kill, Terminate, 
};