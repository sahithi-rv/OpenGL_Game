#include "Projectile.hpp"
//#include "utility.hpp"

Projectile *projectile;
Canon * canon, *base;
//float rec_vel = 0;
/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
     // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
       
    }
    else if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                quit(window);
                break;
            default:
                break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key)
{
	switch (key) {
		case 'Q':
		case 'q':
            quit(window);
            break;
		default:
			break;
	}
}

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods)
{
    switch (button) {
        default:
            break;
    }
}

float camera_rotation_angle = 90;
//float projectile->rectangle_rotation = 0;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw ()
{
  // clear the color and depth in the frame buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // use the loaded shader program
  // Don't change unless you know what you are doing
  glUseProgram (programID);

  // Eye - Location of camera. Don't change unless you are sure!!
  glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
  // Target - Where is the camera looking at.  Don't change unless you are sure!!
  glm::vec3 target (0, 0, 0);
  // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
  glm::vec3 up (0, 1, 0);

  // Send our transformation to the currently bound shader, in the "MVP" uniform
  // For each model you render, since the MVP will be different (at least the M part)
  //  Don't change unless you are sure!!
  projectile->renderProjectile();

  // draw3DObject draws the VAO given to it using current MVP matrix
  draw3DObject(projectile->rectangle);

  // Increment angles
 // float increments = 1;
/****
  canon->renderCanon();
  
  draw3DObject(canon->rectangle);
  base->renderCanon();
  draw3DObject(base->rectangle);
  ****/
  //draw3DObject(canon->base);
  //camera_rotation_angle++; // Simulating camera rotation
  //projectile->rectangle_rotation = projectile->rectangle_rotation + increments*projectile->rectangle_rot_dir*projectile->rectangle_rot_status;
}

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
GLFWwindow* initGLFW (int width, int height)
{
    GLFWwindow* window; // window desciptor/handle

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( 1 );

    /* --- register callbacks with GLFW --- */

    /* Register function to handle window resizes */
    /* With Retina display on Mac OS X GLFW's FramebufferSize
     is different from WindowSize */
    glfwSetFramebufferSizeCallback(window, reshapeWindow);
    glfwSetWindowSizeCallback(window, reshapeWindow);

    /* Register function to handle window close */
    glfwSetWindowCloseCallback(window, quit);

    /* Register function to handle keyboard input */
    glfwSetKeyCallback(window, keyboard);      // general keyboard input
    glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling

    /* Register function to handle mouse click */
    glfwSetMouseButtonCallback(window, mouseButton);  // mouse button clicks

    return window;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
	// Create the models
	//createTriangle (); // Generate the VAO, VBOs, vertices data & copy into the array buffer
  /*GLfloat vertices[]={
    -4,-4,0,
    -4,-2,0,
    -3,-2,0,

    -3,-2,0,
    -3,-4,0,
    -4,-4,0
  };*/
  GLfloat vertices[]={
    0,0,0,
    0,1,0,
    1,1,0,

    1,1,0,
    1,0,0,
    0,0,0
  };

  /***GLfloat vertices[]={
    0,0,0,
    0,2.5,0,
    1,2.5,0,

    1,2.5,0,
    1,0,0,
    0,0,0
  };

  GLfloat base_vertices[]={
    0,0,0,
    0,2,0,
    2,2,0,

    2,2,0,
    2,0,0,
    0,0,0
  };
***/
  GLfloat colors[]={
    1,1,1,
    1,1,1,
    1,1,1,
    
    1,1,1,
    1,1,1,
    1,1,1
  };
  projectile->setInitVertices(vertices);
  projectile->setInitColors(colors);
	projectile->createRectangle ();

 /**** canon->setInitVertices(vertices);
  canon->setInitColors(colors);
  canon->createRectangle ();

  base->setInitVertices(base_vertices);
  base->setInitColors(colors);
  base->createRectangle();
	****/
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

	
	reshapeWindow (window, width, height);

    // Background color of the scene
	glClearColor (0.3f, 0.3f, 0.3f, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main (int argc, char** argv)
{
	int width = 600;
	int height = 600;
    projectile = new Projectile(0,-1*VELOCITY,DISPLACEMENT*0.9,DISPLACEMENT,-4,-4);
    canon = new Canon(0,-4,-3,0);
    base = new Canon(0,-4,-5,0);
    GLFWwindow* window = initGLFW(width, height);

	  initGL (window, width, height);

    double last_update_time = glfwGetTime(), current_time;
    double start_time=last_update_time;
    // Draw in loop
    while (!glfwWindowShouldClose(window)) {

       
        // OpenGL Draw commands
        draw();

        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
        glfwPollEvents();

        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
        if ((current_time - last_update_time) >= 0.1) { // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
            projectile->updatePosition(current_time-start_time);
            //****canon->updateAngle();
            //base->updateAngle();
            //rec_vel+=DISPLACEMENT+VELOCITY*(current_time-start_time);
            last_update_time = current_time;
        }
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
