#pragma once
#include <string>

class DisplayMode
{
public:
	DisplayMode() 
		: width(0) , height(0) 
	{}

	DisplayMode(int w, int h)
		: width(w) , height(h)
	{}

public:
	int width;
	int height;
};


class ContextAttri
{
public:
	ContextAttri() 
		: major(0), minor(0), bProfileCore(false) 
	{}

	ContextAttri(int _major, int _minor) 
		: major(_major), minor(_minor), bProfileCore(false) 
	{}

	void withProfileCore(bool bUseProfile) { bProfileCore = bUseProfile; }

public:
	int major;
	int minor;
	bool bProfileCore;
};

class Display
{
public:
	Display() : title("") {}

	void create(const ContextAttri& context);
	void update();
	void destroy();

	bool isRequestClosed() const;
	bool isKeyPressed(unsigned int keyCode) const;
	void setTitle(const std::string& _title);
	void setDisplayMode(const DisplayMode& displayMode);

private:
	static void frameBufferSizeCallback(struct GLFWwindow* window, int w, int h);
	void processEvent();

private:
	DisplayMode mDisplayMode;
	std::string title;
	struct GLFWwindow* mWindow;
};

