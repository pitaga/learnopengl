#pragma once
#include <memory>

class Render
{
public:
	Render();

	void prepare();

	void onRender(std::shared_ptr<class RawModel>& model);
};

