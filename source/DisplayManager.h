#pragma once
#include <memory>

class DisplayManager
{
public:
	DisplayManager() {}

	void createDisplay();
	void updateDisplay();
	void closeDisplay();

	bool isRequestClosed();

	bool isKeyPressed(unsigned int keyCode);

private:
	std::shared_ptr<class Display> mDisplay;
};

