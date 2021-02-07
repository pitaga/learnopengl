#include "Render.h"
#include "RawModel.h"
#include "glad/glad.h"

Render::Render()
{
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Render::prepare()
{
	glClearColor(0.2, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Render::onRender(std::shared_ptr<RawModel>& model)
{
	if (!model)	return;

	glBindVertexArray(model->getVaoID());
	glEnableVertexAttribArray(0);
	//glDrawArrays(GL_TRIANGLES, 0, model->getVertexCnt());
	glDrawElements(GL_TRIANGLES, model->getVertexCnt(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
