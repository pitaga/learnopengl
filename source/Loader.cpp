#include "Loader.h"
#include "RawModel.h"
#include <glad/glad.h>


std::shared_ptr<RawModel> Loader::loadVao(const std::vector<float>& positions, const int positionSize, const std::vector<unsigned int>& indexs, const int indexSize)
{
    unsigned int vaoID = createVao();
    bindIndexBuffer(indexs, indexSize);
    storeDatatoAttriList(0, positions, positionSize);
    unbindVbo();
    std::shared_ptr<RawModel> model = std::make_shared<RawModel>(vaoID, indexSize / sizeof(unsigned int));
    models.push_back(model);
    return model;
}

void Loader::cleanUp()
{
    if (!models.empty()) {
        models.clear();
    }

    if (!vaos.empty()) {
        glDeleteVertexArrays(vaos.size(), vaos.data());
    }

    if (!vbos.empty()) {
        glDeleteBuffers(vbos.size(), vbos.data());
    }
}

unsigned int Loader::createVao()
{
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    vaos.push_back(vaoID);
    return vaoID;
}

void Loader::unbindVbo()
{
    glBindVertexArray(0);
}

void Loader::bindIndexBuffer(const std::vector<unsigned int>& indexs, const int size)
{
    unsigned int iboID;
    glGenBuffers(1, &iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexs.data(), GL_STATIC_DRAW);
}

void Loader::storeDatatoAttriList(const int index, const std::vector<float>& positions, const int size)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, size, positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(index, 3, GL_FLOAT, false, 3 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vbos.push_back(vboID);
}
