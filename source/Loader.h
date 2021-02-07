#pragma once
#include <vector>
#include <memory>

class Loader
{
public:
	std::shared_ptr<class RawModel> loadVao(const std::vector<float>& positions, const int positionSize, const std::vector<unsigned int>& indexs, const int indexSize);

	void cleanUp();

private:
	unsigned int createVao();

	void unbindVbo();

	void bindIndexBuffer(const std::vector<unsigned int>& indexs, const int size);

	void storeDatatoAttriList(const int index, const std::vector<float>& positions, const int size);

private:
	std::vector<std::shared_ptr<class RawModel>> models;
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
};

