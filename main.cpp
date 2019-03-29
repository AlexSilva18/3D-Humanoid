// Std. Includes
#include <string>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <iostream>
#include <unistd.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void processInputMovement(GLFWwindow *window, int *x, int *y, int *a, int *b, int *c, int *d, int *e, int *f);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float rotation_array[17] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	/*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}*/

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader ourShader("res/shaders/modelLoading.vs", "res/shaders/modelLoading.frag");

	// load models
	// -----------
	//Model ourModel(FileSystem::getPath("resources/objects/nanosuit/nanosuit.obj"));
	//Model ourModel("res/models/nanosuit.obj");
	Model ourModel("res/models/chest_head.obj");
	Model ourModel2("res/models/left_arm_upper.obj");
	Model ourModel3("res/models/left_arm_lower.obj");
	Model ourModel4("res/models/left_leg_lower.obj");
	Model ourModel5("res/models/left_leg_upper.obj");
	Model ourModel6("res/models/right_arm_upper.obj");
	Model ourModel7("res/models/right_arm_lower.obj");
	Model ourModel8("res/models/right_leg_lower.obj");
	Model ourModel9("res/models/right_leg_upper.obj");

	bool fwd = true;
	bool arm_fwd = true;
	bool arm_fwd2 = true;
	bool arm_fwd3 = true;
	bool leg_fwd = true;
	bool leg_fwd2 = true;
	bool leg_lower_fwd = true;
	bool leg_lower_fwd2 = true;
	int x = 0;
	int y = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	int f = 0;
	//float rotation_array[5] = {0, rotation, arm_rotation, leg_rotation, leg_lower_rotation};
// float rotation_array[7] = {1, 0, 0, 0, 0, 0, 0};

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	// render loop
	// -----------
	glm::vec3 xaxis = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 uarm_axis = glm::vec3 (0.0f , -7.0f, 0.0f);


	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	       
		rotation_array[1] += deltaTime;
	        rotation_array[3] += deltaTime;
		rotation_array[5] += deltaTime;
		rotation_array[7] += deltaTime;
		rotation_array[9] += deltaTime;
		rotation_array[11] += deltaTime;
		rotation_array[13] += deltaTime;
		rotation_array[15] += deltaTime;
		rotation_array[17] += deltaTime;
		

		if (fwd) {
		  rotation_array[1] += deltaTime*20;
		  if (rotation_array[1] > 120)
		    fwd = false;
		}
		else {
		  rotation_array[1] -= deltaTime*20;
		  if (rotation_array[1] < 0)
		    fwd = true;
		}

		
		if (arm_fwd){
		  rotation_array[3] += deltaTime*20;
		  if (rotation_array[3] > 100)
		    arm_fwd = false;			  
		}
		else{
		  rotation_array[3] -= deltaTime*20;
		  if (rotation_array[3] < 0)
		    arm_fwd = true;
		}

		if (arm_fwd2){
		  rotation_array[5] += deltaTime*20;
		  if (rotation_array[5] > 100)
		    arm_fwd2 = false;			  
		}
		else{
		  rotation_array[5] -= deltaTime*20;
		  if (rotation_array[5] < 0)
		    arm_fwd2 = true;
		}

		if (arm_fwd3){
		  rotation_array[7] += deltaTime*20;
		  if (rotation_array[7] > 100)
		    arm_fwd3 = false;			  
		}
		else{
		  rotation_array[7] -= deltaTime*20;
		  if (rotation_array[7] < 0)
		    arm_fwd3 = true;
		}

		if (leg_fwd){
		  rotation_array[9] += deltaTime*20;
		  if (rotation_array[9] > 70)
		    leg_fwd = false;
				  
		}
		else{
		  rotation_array[9] -= deltaTime*20;
		  if (rotation_array[9] < -30)
		    leg_fwd = true;
		}

		if (leg_fwd2){
		  rotation_array[11] += deltaTime*20;
		  if (rotation_array[11] > 90)
		    leg_fwd2 = false;
				  
		}
		else{
		  rotation_array[11] -= deltaTime*20;
		  if (rotation_array[11] < 10)
		    leg_fwd2 = true;
		}

		if (leg_lower_fwd){
		  rotation_array[13] += deltaTime*20;
		  if (rotation_array[13] > 70)
		    leg_lower_fwd = false;
				  
		}
		else{
		  rotation_array[13] -= deltaTime*20;
		  if (rotation_array[13] < -30)
		    leg_lower_fwd = true;
		}

		if (leg_lower_fwd2){
		  rotation_array[15] += deltaTime*20;
		  if (rotation_array[15] > 90)
		    leg_lower_fwd2 = false;
				  
		}
		else{
		  rotation_array[15] -= deltaTime*20;
		  if (rotation_array[15] < 10)
		    leg_lower_fwd2 = true;
		}
	        
		// input
		// -----
		processInput(window);
		processInputMovement(window, &x, &y, &a, &b, &c, &d, &e, &f);

		// render
		// ------
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		ourShader.use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		// render the loaded model
		glm::mat4 chest = glm::mat4(1.0f);
		ourShader.setMat4("model", chest);
		ourModel.Draw(ourShader);

		glm::mat4 left_upper_arm = glm::mat4(1.0f);
		left_upper_arm = glm::translate(left_upper_arm, glm::vec3 (0.0f , 12.0f, 0.0f));
		left_upper_arm=glm::rotate(left_upper_arm,glm::radians((GLfloat)-rotation_array[a]),xaxis);
		left_upper_arm = glm::translate(left_upper_arm, glm::vec3(0.0f, -12.0f, 0.0f));
		
		ourShader.setMat4("model", left_upper_arm);
		ourModel2.Draw(ourShader);

		glm::mat4 left_lower_arm = glm::mat4(1.0f);
		left_lower_arm = glm::translate(left_lower_arm, glm::vec3 (0.0f , 12.0f, 0.0f));
		left_lower_arm=glm::rotate(left_lower_arm,glm::radians((GLfloat)-rotation_array[a]),xaxis);
		left_lower_arm = glm::translate(left_lower_arm, glm::vec3(0.0f, -12.0f, 0.0f));
		
	        left_lower_arm = glm::translate(left_lower_arm, glm::vec3 (0.0f , 10.0f, 0.0f));
	        left_lower_arm=glm::rotate(left_lower_arm,glm::radians((GLfloat)-rotation_array[b]),xaxis);
	        left_lower_arm = glm::translate(left_lower_arm, glm::vec3(0.0f, -10.0f, 0.0f));
		
		ourShader.setMat4("model", left_lower_arm);
		ourModel3.Draw(ourShader);

		
		glm::mat4 right_upper_arm = glm::mat4(1.0f);
	        right_upper_arm = glm::translate(right_upper_arm, glm::vec3 (0.0f , 12.0f, 0.0f));
		right_upper_arm=glm::rotate(right_upper_arm,glm::radians((GLfloat)-rotation_array[x]),xaxis);
	        right_upper_arm = glm::translate(right_upper_arm, glm::vec3(0.0f, -12.0f, 0.0f));
		
		ourShader.setMat4("model", right_upper_arm);
		ourModel6.Draw(ourShader);

		glm::mat4 right_lower_arm = glm::mat4(1.0f);
		right_lower_arm = glm::translate(right_lower_arm, glm::vec3 (0.0f , 12.0f, 0.0f));
		right_lower_arm=glm::rotate(right_lower_arm,glm::radians((GLfloat)-rotation_array[x]),xaxis);
		right_lower_arm = glm::translate(right_lower_arm, glm::vec3(0.0f, -12.0f, 0.0f));
		
	        right_lower_arm = glm::translate(right_lower_arm, glm::vec3 (0.0f , 10.5f, 0.0f));
		right_lower_arm=glm::rotate(right_lower_arm,glm::radians((GLfloat)-rotation_array[y]),xaxis);
	        right_lower_arm = glm::translate(right_lower_arm, glm::vec3(0.0f, -10.5f, 0.0f));

		ourShader.setMat4("model", right_lower_arm);
		ourModel7.Draw(ourShader);

		
		glm::mat4 left_upper_leg = glm::mat4(1.0f);
	        left_upper_leg = glm::translate(left_upper_leg, glm::vec3 (0.0f , 8.0f, 0.0f));
	        left_upper_leg=glm::rotate(left_upper_leg,glm::radians((GLfloat)-rotation_array[c]),xaxis);
	        left_upper_leg = glm::translate(left_upper_leg, glm::vec3(0.0f, -8.0f, 0.0f));
		
		ourShader.setMat4("model", left_upper_leg);
		ourModel5.Draw(ourShader);

		glm::mat4 left_lower_leg = glm::mat4(1.0f);
		left_lower_leg = glm::translate(left_lower_leg, glm::vec3 (0.0f , 8.0f, 0.0f));
	        left_lower_leg=glm::rotate(left_lower_leg,glm::radians((GLfloat)-rotation_array[c]),xaxis);
	        left_lower_leg = glm::translate(left_lower_leg, glm::vec3(0.0f, -8.0f, 0.0f));
		
	        left_lower_leg = glm::translate(left_lower_leg, glm::vec3 (0.0f , 4.0f, 0.0f));
	        left_lower_leg=glm::rotate(left_lower_leg,glm::radians((GLfloat)rotation_array[d]),xaxis);
	        left_lower_leg = glm::translate(left_lower_leg, glm::vec3(0.0f, -4.0f, 0.0f));
		
		ourShader.setMat4("model", left_lower_leg);
		ourModel4.Draw(ourShader);


		glm::mat4 right_upper_leg = glm::mat4(1.0f);
	        right_upper_leg = glm::translate(right_upper_leg, glm::vec3 (0.0f , 8.0f, 0.0f));
	        right_upper_leg=glm::rotate(right_upper_leg,glm::radians((GLfloat)-rotation_array[e]),xaxis);
	        right_upper_leg = glm::translate(right_upper_leg, glm::vec3(0.0f, -8.0f, 0.0f));
		
		ourShader.setMat4("model", right_upper_leg);
		ourModel9.Draw(ourShader);

		glm::mat4 right_lower_leg = glm::mat4(1.0f);
		right_lower_leg = glm::translate(right_lower_leg, glm::vec3 (0.0f , 8.0f, 0.0f));
	        right_lower_leg=glm::rotate(right_lower_leg,glm::radians((GLfloat)-rotation_array[e]),xaxis);
	        right_lower_leg = glm::translate(right_lower_leg, glm::vec3(0.0f, -8.0f, 0.0f));
		
		right_lower_leg = glm::translate(right_lower_leg, glm::vec3 (0.0f , 4.0f, 0.0f));
		right_lower_leg=glm::rotate(right_lower_leg,glm::radians((GLfloat)rotation_array[f]),xaxis);
	        right_lower_leg = glm::translate(right_lower_leg, glm::vec3(0.0f, -4.0f, 0.0f));
		
		ourShader.setMat4("model", right_lower_leg);
		ourModel8.Draw(ourShader);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void processInputMovement(GLFWwindow *window, int *x, int *y, int *a, int *b, int *c, int *d, int *e, int *f)
{

  float temp = 0;
  float temp2 = 0;
  float temp3 = 0;
  float temp4 = 0;
  float temp5 = 0;
  float temp6 = 0;
  float temp7 = 0;
  float temp8 = 0;
  
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
	  *x = 1;

	  temp = rotation_array[1];
	  rotation_array[2] = temp;
	  *x = 2;

	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS){
	  *y = 3;
	  temp2 = rotation_array[3];
	  rotation_array[4] = temp2;
	  *y = 4;
	}
	
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS){
	  *a = 5;
	  temp3 = rotation_array[5];
	  rotation_array[6] = temp3;
	  *a = 6;

	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS){
	  *b = 7;
	  temp4 = rotation_array[7];
	  rotation_array[8] = temp4;
	  *b = 8;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS){
	  *c = 9;
	  temp5 = rotation_array[9];
	  rotation_array[10] = temp5;
	  *c = 10;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS){
	  *d = 11;
	  temp6 = rotation_array[11];
	  rotation_array[12] = temp6;
	  *d = 12;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS){
	  *e = 13;
	  temp7 = rotation_array[13];
	  rotation_array[14] = temp7;
	  *e = 14;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS){
	  *f = 15;
	  temp8 = rotation_array[15];
	  rotation_array[16] = temp8;
	  *f = 16;
	}


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
