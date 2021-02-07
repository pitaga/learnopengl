#include "DisplayManager.h"
#include "Loader.h"
#include "RawModel.h"
#include "Render.h"
#include "StaticShader.h"
#include "MathTools.h"
#include <GLFW/glfw3.h>


int main()
{
    //   0/----------------/1
    //   /|               /|
    //  / |              / |
    //4/--|-------------/5 |
    // |  |             |  |
    // |  |             |  |
    // |  |             |  |
    // | 3/-------------|--/2
    // | /              | /
    // |/               |/
    //7/----------------/6

    std::vector<float> positions = {
        -0.5f,      0.5f,       -0.5f,
        0.5f,       0.5f,       -0.5f,
        0.5f,       -0.5f,      -0.5f,
        -0.5f,      -0.5f,      -0.5f,
        -0.5f,      0.5f,       0.5f,
        0.5f,       0.5f,       0.5f,
        0.5f,       -0.5f,      0.5f,
        -0.5f,      -0.5f,      0.5f,
    };

    std::vector<unsigned int> indexs = {
        1, 5, 0, 0, 5, 4,
        0, 4, 3, 3, 4, 7,
        3, 2, 6, 3, 6, 7,
        5, 2, 6, 5, 1, 2,
        4, 5, 6, 4, 6, 7,
        0, 1, 3, 1, 2, 3
    };


	std::shared_ptr<DisplayManager> displayManager = std::make_shared<DisplayManager>();
    std::shared_ptr<Loader> loader = std::make_shared<Loader>();
    std::shared_ptr<Render> render = std::make_shared<Render>();

	displayManager->createDisplay();
    std::shared_ptr<RawModel> model = loader->loadVao(positions, positions.size() * sizeof(float), indexs, indexs.size() * sizeof(int));

    std::shared_ptr<StaticShader> shader = std::make_shared<StaticShader>();

	while (!displayManager->isRequestClosed())
	{
        shader->start();
        shader->loadTransformMatrix(GLMath::createTransformMatrix(glm::vec3(), (float)glfwGetTime() * 45, 0, (float)glfwGetTime() * 45, 1.0));
        render->prepare();
        render->onRender(model);
        shader->stop();
		
        displayManager->updateDisplay();
		if (displayManager->isKeyPressed(GLFW_KEY_R)) {
            shader->reloadShader();
		}
	}

    shader->cleanUp();
    loader->cleanUp();
	displayManager->closeDisplay();
	return 0;
}