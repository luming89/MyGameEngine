#include <iostream>
#include <GL\glew.h>
#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 1024
#define HEIGHT 768
#define TITLE "Luming's Game Engine"

int main(int argc, char** argv)
{
	Display display(WIDTH, HEIGHT, TITLE);

	Vertex vertices[] = {	Vertex(glm::vec3(-0.5, -0.5, 0),glm::vec2(0.0,0.0)),
							Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
							Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

	unsigned int indices[] = { 0, 1, 2 };

	Shader shader("../../res/basicShader");
	//Texture texture("./res/bricks.jpg");
	Texture texture("../../res/Rusted_Steel.jpg");
	Transform transform;
	Camera camera(glm::vec3(0, 100, -200), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	float counter = 0.0f;

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Mesh monkey("../../res/monkey3.obj");
	Mesh eiffel("../../res/Eiffel.obj");

	while (display.IsClosed() == false)
	{
		display.Clear(0.0f, 0.2f, 0.4f, 1.0f);
		transform.GetPos().x = sinf(counter);
		transform.GetRot().y = 100*counter;
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform,camera);
		//mesh.Draw();
		//monkey.Draw();
		eiffel.Draw();
		display.Update();
		counter += 0.001f;
	}
	
	return 0;
}