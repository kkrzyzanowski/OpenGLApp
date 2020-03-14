#include <GL\glew.h>
#include <GLFW/glfw3.h>
class Controls
{
public:
	Controls(GLFWwindow *window);
	void MouseLeftButtonClick();
	~Controls();
private: 
	GLFWwindow* window;
};

