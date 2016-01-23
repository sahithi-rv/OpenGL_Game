#include "Projectile.hpp"
//#include "utility.hpp"

Circle *projectile,*hinge;
Quadrilateral * canon, *base, *obstacles[15], *bar[15], *tar;

Quadrilateral * boundary_bottom, *boundary_top, *boundary_left, *boundary_right;
bool motion_phase_projectile = false, motion_phase_start_projectile = false;
double motion_start_time;
double projectile_init_vx,projectile_init_vy;
//float rec_vel = 0;
/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
     // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
      switch (key) {
            case GLFW_KEY_SPACE:
                motion_start_time = glfwGetTime();
                motion_phase_start_projectile = true;
                break;
            case GLFW_KEY_D:
                canon->updatePosition(CANON_STEP);
                break;
            case GLFW_KEY_A:
                canon->updatePosition(-1*CANON_STEP);
                break;
            case GLFW_KEY_W:
                canon->updateAngle(-1*CANON_ROTATION,0,90);
                break;
            case GLFW_KEY_S:
                canon->updateAngle(CANON_ROTATION,0,90);
                break;
            case GLFW_KEY_UP:
                if(speed_level<10)
                  speed_level++;
                break;

            case GLFW_KEY_DOWN:
                if(speed_level>0)
                  speed_level--;
                break;

      }
       
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
  /***obs->renderObstacle();
  draw3DObject(obs->circle);
  ****/
  //  Don't change unless you are sure!!
 
  // Increment angles
 // float increments = 1;
  if(motion_phase_projectile){
    projectile->renderCircle();
    draw3DObject(projectile->circle);
  }
  canon->renderQuad();
  draw3DObject(canon->rectangle);
  base->renderQuad();
  draw3DObject(base->rectangle);
  
  tar->renderQuad();
  draw3DObject(tar->rectangle);

  boundary_bottom->renderQuad();
  draw3DObject(boundary_bottom->rectangle);
 /* boundary_left->renderQuad();
  draw3DObject(boundary_left->rectangle);
  boundary_top->renderQuad();
  draw3DObject(boundary_top->rectangle);
  */
  boundary_right->renderQuad();
  draw3DObject(boundary_right->rectangle);

  
  //obstacle1->renderQuad();
  //draw3DObject(obstacle1->rectangle);

  for(int i=0;i<=speed_level;i++){
        
      bar[i]->renderQuad();
      draw3DObject(bar[i]->rectangle);
  }

  for(int i=0;i<STATIC_OBSTACLES;i++){
    obstacles[i]->renderQuad();
    draw3DObject(obstacles[i]->rectangle);
  }

  hinge->renderCircle();
  draw3DObject(hinge->circle);
  
  /****
 
  obstacle->renderCanon();
  draw3DObject(obstacle->rectangle);
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

void setInitials(Quadrilateral *box,float r,float g,float b){

  GLfloat * vertex_buffer_data;
  vertex_buffer_data = box->getInitVertices();
  GLfloat * colors = box->getInitColors(r,g,b);
  box->setInitVertices(vertex_buffer_data);
  box->setInitColors(colors);
  box->createRectangle ();
}



/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
  GLfloat vertices[]={
    0,0,0,
    0,1,0,
    1,1,0,

    1,1,0,
    1,0,0,
    0,0,0
  };

  GLfloat obstacle_vertices[]={
    0,0,0,
    0,3,0,
    0.5,3,0,

    0.5,3,0,
    0.5,0,0,
    0,0,0
  };

  setInitials(canon,0.870588, 0.721569, 0.529412);
  setInitials(base,0.372549, 0.619608, 0.627451);
  
  setInitials(boundary_bottom,1,1,1);
  //setInitials(boundary_top);
  //setInitials(boundary_left);
  setInitials(boundary_right,1,1,1);

  setInitials(tar,0.8,0.1,0);

  GLfloat * hinge_vertices = circleVertices(hinge->num_vertices, hinge->radius);
  GLfloat * hinge_colors = circleColors(hinge->num_vertices,0.662745, 0.662745, 0.662745);

  hinge->setInitVertices(hinge_vertices);
  hinge->setInitColors(hinge_colors);
  hinge->createCircle();
  for(int i=0;i<STATIC_OBSTACLES;i++){
   setInitials(obstacles[i],0.823529, 0.411765, 0.117647);
  }
 // setInitials(obstacle1,1,1,1);
  for(int i=0;i<=10;i++){
      setInitials(bar[i],float(i)/10,1-float(i)/10,0);
  }
 
/****
  obstacle->setInitVertices(obstacle_vertices);
  obstacle->setInitColors(colors);
  obstacle->createRectangle();
  ***/
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
//no need of centre
void onCollision(Circle * granade,Quadrilateral * obstacle,pair<float,float> centre,float rad){
  float x1 = granade->getX() , y1 = granade->getY();
  float vx = granade->getVX() , vy = granade->getVY();
  double theta = atan2(vy,vx);
  float displace = obstacle->boundary_radius + granade->getRadius();
  //output2(granade->getX(),granade->getY());
  if(vx>=0)
    granade->setX(x1-displace);
  else
    granade->setX(x1+displace);
  if(vy>=0)
    granade->setY(y1-displace);
  else
    granade->setY(y1+displace);
  if(abs(x1-(obstacle->getX()))<=0.5 && abs(y1-(obstacle->getY()))<=0.5){
    if((vx>0 && vy>0)){
      granade->setX(x1-displace);
      granade->setY(y1-displace);
    }
  }
  else if(abs(x1-(obstacle->getX()))<=0.5 && abs(y1-(obstacle->getY()+obstacle->getSideY()))<=0.5){
     if((vx>0 && vy<0)){
      granade->setX(x1-displace);
      granade->setY(y1+displace);
    }
  }
  else if(abs(x1-(obstacle->getX()+obstacle->getSideX()))<=0.5 && abs(y1-(obstacle->getY()+obstacle->getSideY()))<=0.5){
   if((vx<0 && vy<0)){
      granade->setX(x1+displace);
      granade->setY(y1+displace);
    }
  }
  else if(abs(x1-(obstacle->getX()+obstacle->getSideX()))<=0.5 && abs(y1-(obstacle->getY()))<=0.5){
     if(!(vx<0 && vy>0)){
      granade->setX(x1+displace);
      granade->setY(y1-displace);
    }
  }

  
 // output2(granade->getX(),granade->getY());
  theta += M_PI;
 // output2(x1,y1);
  //output2(vx,vy);
  //output1(theta);
  double v = sqrt(vx*vx + vy*vy );
  //output1(v);
  double finalv = obstacle->cor * v;
  // output1(finalv);
  granade->setVX(finalv*cos(theta));
  granade->setVY(finalv*sin(theta));
  //output2(finalv*cos(theta),finalv*sin(theta));
  //cout << " in " <<granade->getVY() << endl;
}

bool checkCollision(Circle granade,Quadrilateral obstacle,pair<float,float> * centre,float * bound_rad){
  TR( obstacle.boundary_points, it){
    //output2((*it).F,(*it).S);
    float dt = distance(granade.getX(),granade.getY(),(*it).F,(*it).S );
    //output1(dt);
    if( obstacle.boundary_radius + granade.getRadius() >= dt ){
      *centre = MP((*it).F,(*it).S );
      *bound_rad = obstacle.boundary_radius;
      return true;
    }
  }
  return false;
}

void setBoundaries(Quadrilateral *obstacle){
    obstacle->setBoundaryPoints(obstacle->getX(),obstacle->getY(),obstacle->getX(),obstacle->getY()+obstacle->getSideY());
    obstacle->setBoundaryPoints(obstacle->getX(),obstacle->getY()+obstacle->getSideY(),obstacle->getX()+obstacle->getSideX(),obstacle->getY()+obstacle->getSideY());
    obstacle->setBoundaryPoints(obstacle->getX()+obstacle->getSideX(),obstacle->getY()+obstacle->getSideY(),obstacle->getX()+obstacle->getSideX(),obstacle->getY());
    obstacle->setBoundaryPoints(obstacle->getX()+obstacle->getSideX(),obstacle->getY(),obstacle->getX(),obstacle->getY());

}

pair<pair<float,float>,pair<float,float> > getProjectileInitPosition(Quadrilateral canon){
  double theta = canon.getAngle()*M_PI/180;
  float x1 = canon.getX() , y1 = canon.getY();
  float rx= canon.getSideX() , ry = canon.getSideY();
  
  float y = y1 + ry*cos(theta);
  float x = x1 + ry*sin(theta);
  y = y + rx/2*cos(M_PI/2 - theta);
  //output1(sin(M_PI/2 - theta));
  x = x + rx/2*sin(M_PI/2 - theta);
  //output2(x,y);
  return MP(MP(x,y),MP(cos(M_PI/2 - theta),sin(M_PI/2 - theta)));
}

int main (int argc, char** argv)
{
  int theta=1.5;
	 int width = SCREEN_WIDTH;
	 int height = SCREEN_HEIGHT;
   int projectile_collision_count,flag=0;
   float collide_vel;
   speed_level=0;
    //**** 
    canon = new Quadrilateral(0,-3.5,-3,0,0.5,3,0,0.05,0.2,0,10000,1);
    base = new Quadrilateral(0,-3.5,-4,0,2.5,1,0,0.05,0.2,0,10000,1);

    boundary_bottom = new Quadrilateral(0,-4,-4,0,8,0.2,0,0.05,0.9,0,10000,1);
   // boundary_top = new Quadrilateral(0,-4,3.8,0,8,0.2,0.1);
    //boundary_left = new Quadrilateral(0,3.8,-4,0,0.2,8,0.1);
    boundary_right = new Quadrilateral(0,-4.1,-4,0,0.2,8,0,0.05,0.2,0,10000,1);
    tar = new Quadrilateral(0,2.8,-2,0,0.8,0.2,0,0.05,0.2,0,10000,1);
    /*****/
    obstacles[0] = new Quadrilateral(0,1.3,3.5,0,1.7,0.5,0,0.05,0.3,0,10000,1);
    obstacles[1] = new Quadrilateral(330,3.7,2.2,0,0.4,2,0,0.05,0.3,0,10000,1);
    obstacles[2] = new Quadrilateral(0,3.7,-1.5,0,0.3,4,0,0.05,0.3,0,10000,1);
    obstacles[3] = new Quadrilateral(0,2.3,-1.5,0,0.3,3.3,0,0.05,0.3,0,10000,1);
    obstacles[4] = new Quadrilateral(0,1.5,3.8,0,0.3,-1.8,0,0.05,0.3,0,10000,1);

    hinge = new Circle(360,0,0,0,0,1.65,3.8,0,0.05,0,0);
    //obstacles[1] = new Quadrilateral()
    /*****/
    //obstacle1 = new Quadrilateral(0,0,-3,0,0.5,3,0,0.1,0.3,0,10000,1);
    //bar = new Quadrilateral(0,-3.5,3.25,0,2,0.5,0,1,0,0,0);
    for(int i=0;i<=10;i++){
      bar[i] = new Quadrilateral(0,-3.5+float(i)/8,3.25,0,0.125,0.5,0,0,1,0,0,1); 
    }
    GLFWwindow* window = initGLFW(width, height);
	  initGL (window, width, height);
    double last_update_time = glfwGetTime(), current_time;
    double start_time=last_update_time;
    // Draw in loop
    pair <float,float> centre;float rad;

    boundary_right->setBoundaryPoints(boundary_right->getX()+boundary_right->getSideX(),boundary_right->getY()+boundary_right->getSideY(),boundary_right->getX()+boundary_right->getSideX(),boundary_right->getY());
    for(int i=0;i<STATIC_OBSTACLES-1;i++){
     setBoundaries(obstacles[i]);
    }
    while (!glfwWindowShouldClose(window)) {

       
        // OpenGL Draw commands
        draw();

        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
        glfwPollEvents();
        
        if(motion_phase_start_projectile){
          pair<pair<float,float>,pair<float,float> > dis;
          
          motion_phase_projectile = true;
          dis=getProjectileInitPosition(*canon);
          float displace = DISPLACEMENT + (float)speed_level/10;
          projectile = new Circle(360,0,-1*VELOCITY,displace*dis.S.F,displace*dis.S.S,dis.F.F,dis.F.S,0,0.25,0,0);
          GLfloat * circle_vertices = circleVertices(projectile->num_vertices, projectile->radius);
          GLfloat * circle_colors = circleColors(projectile->num_vertices,1, 0.498039, 0.313725);

          projectile->setInitVertices(circle_vertices);
          projectile->setInitColors(circle_colors);
          projectile->createCircle();

          
          motion_phase_start_projectile = false;
         projectile_collision_count=0;

        }

        

        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
        if ((current_time - last_update_time) >= 0.05) { // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..

          if(motion_phase_projectile ){
            if(projectile->getY()<=-3.5){
              
              float ax= MEW*VELOCITY;
              if(!flag){
                collide_vel=projectile->getVX();
              if(collide_vel>0)
                projectile->setAX(-1*ax);
              else if(collide_vel<0)
                projectile->setAX(ax);
                flag=1;
              }
              if(collide_vel*projectile->getVX()<=0){
                projectile->setAX(0);
                projectile->setVX(0);
              }
              projectile->setY(-3.6);
              projectile->setVY(0);
              projectile->setAY(0);
             // output2(projectile->getAX(),projectile->getVX());
            }
          }

          setBoundaries(obstacles[4]);
          if(motion_phase_projectile && checkCollision(*projectile,*boundary_right,&centre,&rad)){
            onCollision(projectile,boundary_right,centre,rad);
          }
            
            for(int i=0;i<STATIC_OBSTACLES;i++){
              if(motion_phase_projectile && checkCollision(*projectile,*obstacles[i],&centre,&rad)){
                onCollision(projectile,obstacles[i],centre,rad);
               }
            }
            if(motion_phase_projectile){
              projectile->updatePosition(current_time-motion_start_time);
            }
            if(obstacles[4]->getAngle()>=23 || obstacles[4]->getAngle()<=-23)
              theta*=-1;
            obstacles[4]->updateAngle(theta,-25,25);
            //****canon->updateAngle();
            //base->updateAngle();
            //rec_vel+=DISPLACEMENT+VELOCITY*(current_time-start_time);
            last_update_time = current_time;
        }
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
