#include "Projectile.hpp"
//#include "utility.hpp"

Circle *projectile,*hinge, *borders[5][4];
Quadrilateral * canon, *base, *obstacles[15], *bar[15], *tar, *button , *button_base;

Quadrilateral * boundary_bottom, *boundary_top, *boundary_left, *boundary_right;
bool motion_phase_projectile = false, motion_phase_start_projectile = false, stop_oscillation = false, bound = true, bound1 = true;
double motion_start_time;
double projectile_init_vx,projectile_init_vy;
Quadrilateral * back_floor, *back_lines[BACK_LINES];
Line * paint[PAINT];
Circle * back_circles[CIRCLE];
Line * lines[LINES];


int ATTEMPT;

 Circle * attempt[10000];
//float rec_vel = 0;
/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
     // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
      switch (key) {
            case GLFW_KEY_SPACE:
            //if(!motion_phase_projectile && !motion_phase_start_projectile){
                motion_start_time = glfwGetTime();
                motion_phase_start_projectile = true;
              //}
                break;
            case GLFW_KEY_D:
                canon->updatePosition(CANON_STEP,-6.8,-4.8);
                break;
            case GLFW_KEY_A:
                canon->updatePosition(-1*CANON_STEP,-6.8,-4.8);
                break;
            case GLFW_KEY_W:
                canon->updateAngle(CANON_ROTATION,0,-90,1);
                break;
            case GLFW_KEY_S:
                canon->updateAngle(-1*CANON_ROTATION,0,-90,1);
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
   back_floor->renderQuad();
   draw3DObject(back_floor->rectangle);

   for(int i=0;i<BACK_LINES;i++){
    back_lines[i]->renderQuad();
    draw3DObject(back_lines[i]->rectangle);
   }

   for(int i=0;i<PAINT;i++){
    paint[i]->renderLine();
    draw3DObject(paint[i]->line);
   }

   for(int i=0;i<CIRCLE;i++){
    back_circles[i]->renderCircle();
    draw3DObject(back_circles[i]->circle);
  }



   for(int i=0;i<STATIC_OBSTACLES;i++){
    obstacles[i]->renderQuad();
    draw3DObject(obstacles[i]->rectangle);
  }
  
for(int j=0;j<5;j++){
  for(int i=0;i<4;i++){
    borders[j][i]->renderCircle();
    draw3DObject(borders[j][i]->circle);
  }
}

  canon->renderQuad();
  draw3DObject(canon->rectangle);
  base->renderQuad();
  draw3DObject(base->rectangle);

  button_base->renderQuad();
  draw3DObject(button_base->rectangle);


  button->renderQuad();
  draw3DObject(button->rectangle);

  tar->renderQuad();
  draw3DObject(tar->rectangle);

  for(int i=0;i<LINES;i++){
    lines[i]->renderLine();
    draw3DObject(lines[i]->line);
  }

  for(int i=0;i<=speed_level;i++){
        
      bar[i]->renderQuad();
      draw3DObject(bar[i]->rectangle);
  }

  if(motion_phase_projectile){
    projectile->renderCircle();
    draw3DObject(projectile->circle);
  }

/****  

  
  
 
  
  boundary_bottom->renderQuad();
  draw3DObject(boundary_bottom->rectangle);
  boundary_right->renderQuad();
  draw3DObject(boundary_right->rectangle);

  
  
  

  

  

  hinge->renderCircle();
  draw3DObject(hinge->circle);

  *****/
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

void setInitials(Quadrilateral *box,float r,float g,float b,GLfloat * vertex_buffer_data){


  GLfloat * colors = box->getInitColors(r,g,b);
  box->setInitVertices(vertex_buffer_data);
  box->setInitColors(colors);
  box->createRectangle ();
}

void setInitials(Line *box,float r,float g,float b){

  GLfloat * vertex_buffer_data;
  vertex_buffer_data = box->getInitVertices();
  GLfloat * colors = box->getInitColors(r,g,b);
  box->setInitVertices(vertex_buffer_data);
  box->setInitColors(colors);
  box->createLine();
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
  
for(int i=0;i<STATIC_OBSTACLES;i++){
   setInitials(obstacles[i],1, 0.54902, 0);
  }

  GLfloat * hinge_vertices = circleVertices(borders[0][0]->num_vertices, borders[0][0]->radius);
  GLfloat * hinge_colors = circleColors(borders[0][0]->num_vertices,0.662745, 0.662745, 0.662745);
for(int j=0;j<5;j++){
  for(int i=0;i<4;i++){
    borders[j][i]->setInitVertices(hinge_vertices);
    borders[j][i]->setInitColors(hinge_colors);
    borders[j][i]->createCircle();
  }
}

/*for (int i = 0; i < ATTEMPT; ++i)
{
  attempt[i]->setInitVertices(hinge_vertices);
    attempt[i]->setInitColors(hinge_colors);
    attempt[i]->createCircle();
}
*/
GLfloat * circle_vertices , * circle_colors;
for(int i=0;i<CIRCLE;i++){
  circle_vertices = circleVertices(back_circles[i]->num_vertices,back_circles[i]->radius);
  circle_colors = circleColors(back_circles[i]->num_vertices,1,1,1);
  back_circles[i]->setInitVertices(circle_vertices);
    back_circles[i]->setInitColors(circle_colors);
    back_circles[i]->createCircle();
}

setInitials(canon,1, 0.870588, 0.678431);
  setInitials(base,0, 0, 0.501961);

  setInitials(tar,0.8,0.1,0);

  for(int i=0;i<=10;i++){
      setInitials(bar[i],float(i)/10,1-float(i)/10,0);
  }

/***
  
  
  setInitials(boundary_bottom,1,1,1);
  //setInitials(boundary_top);
  //setInitials(boundary_left);
  setInitials(boundary_right,1,1,1);

  

  

  hinge->setInitVertices(hinge_vertices);
  hinge->setInitColors(hinge_colors);
  hinge->createCircle();

  


  
 // setInitials(obstacle1,1,1,1);
  
***/
  GLfloat button_base_vertices[] = {
    0,0,0,
    0,0.8,0,
    1.5,1.25,0,

    1.5,1.25,0,
    1.5,-0.45,0,
    0,0,0

  } ;

  GLfloat * colors = button_base->getInitColors(0.741176, 0.717647, 0.419608);
  button_base->setInitVertices(button_base_vertices);
  button_base->setInitColors(colors);
  button_base->createRectangle();

  GLfloat back_floor_vertices[]={
    -10,-4,0,
    -9,4,0,
    10,4,0,

    10,4,0,
    10,-4,0,
    -10,-4,0,

  };

  colors = back_floor->getInitColors(0.721569, 0.52549, 0.0431373);
  back_floor->setInitVertices(back_floor_vertices);
  back_floor->setInitColors(colors);
  back_floor->createRectangle();

 GLfloat back_line1[]={
   -0.25,-4,0,
    0,4,0,
    0.25,4,0,

    0.25,4,0,
    0,-4,0,
    -0.25,-4,0,
  };
  setInitials(back_lines[0],1, 1, 0.941176,back_line1);

  for(int i = 0 ;i<PAINT;i++){
    setInitials(paint[i],1, 1, 0.941176);
  }
 /* GLfloat back_line2[]={
    -8,-2,0,
    -8.3,-1.7,0,
    -4,-0.7,0,
    
    -4,-0.7,0,
    -3.7,-1,0,
    -8,-2,0,
  };
  setInitials(back_lines[1],1, 1, 0.941176,back_line2);*/


  setInitials(button,0.862745, 0.0784314, 0.235294);

  for(int i=0;i<LINES;i++)
    setInitials(lines[i],1,1,1);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

	
	reshapeWindow (window, width, height);

    // Background color of the scene
	glClearColor ( 1, 0.980392, 0.803922 ,0.f); // R, G, B, A
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
  obstacle->boundary_points.clear();
  //output1(SZ(obstacle->boundary_points));
  double theta = obstacle->getAngle();
  theta = 270 - theta;
  float sx = abs(obstacle->getSideX() ) , sy = abs(obstacle->getSideY()) ;
  float x1 = obstacle->getX(), y1 = obstacle->getY(); 
  float sxc = sx*cos(theta*M_PI/180.0f) , sxs = sx*sin(theta*M_PI/180.0f);
  float syc  = sy*cos(theta*M_PI/180.0f), sys = sy*sin(theta*M_PI/180.0f);
  /*if(bound1 && !bound){
      output1(SZ(obstacle->boundary_points));

    output2(x1,y1);
    output2(x1+syc,y1+syc);
    output1(theta);
    output2(cos(theta*M_PI/180),sin(theta*M_PI/180));
  }*/
    obstacle->setBoundaryPoints(x1,y1,x1+syc,y1+sys);
    theta += 90;
    x1+=syc;
    y1+=syc;
    sxc = sx*cos(theta*M_PI/180.0f) , sxs = sx*sin(theta*M_PI/180.0f);
   syc  = sy*cos(theta*M_PI/180.0f), sys = sy*sin(theta*M_PI/180.0f);
    
    obstacle->setBoundaryPoints(x1,y1,x1+sxc,y1+sxs);
    theta += 90;
    x1+=sxc;
    y1+=sxs;
    sxc = sx*cos(theta*M_PI/180.0f) , sxs = sx*sin(theta*M_PI/180.0f);
   syc  = sy*cos(theta*M_PI/180.0f), sys = sy*sin(theta*M_PI/180.0f);

    obstacle->setBoundaryPoints(x1,y1,x1+syc,y1+sys);
    theta += 90;
    x1+=syc;
    y1+=syc;
    sxc = sx*cos(theta*M_PI/180.0f) , sxs = sx*sin(theta*M_PI/180.0f);
   syc  = sy*cos(theta*M_PI/180.0f), sys = sy*sin(theta*M_PI/180.0f);

 
    obstacle->setBoundaryPoints(x1,y1,x1+sxc,y1+sxs);
  
}

pair<pair<float,float>,pair<float,float> > getProjectileInitPosition(Quadrilateral canon){
  double theta = canon.getAngle();
 // output1(theta);

  theta*=-1*M_PI/180.0f;
  float x1 = canon.getX() , y1 = canon.getY();
  float rx= canon.getSideX() , ry = canon.getSideY();
  
 // output2(x1,y1);
 // output2(rx,ry);

  float y = y1 + ry*cos(theta);
  float x = x1 + ry*sin(theta);
  y = y + rx/2*cos(M_PI/2 - theta);
  //output1(sin(M_PI/2 - theta));
  x = x + rx/2*sin(M_PI/2 - theta);
 // output2(x,y);
  return MP(MP(x,y),MP(cos(M_PI/2 - theta),sin(M_PI/2 - theta)));
}

int main (int argc, char** argv)
{
  float theta=1;
	 int width = SCREEN_WIDTH;
	 int height = SCREEN_HEIGHT;
   int projectile_collision_count,flag=0;
   float collide_vel;
   speed_level=0;

  obstacles[0] = new Quadrilateral(1,9.7,0,0,0.3,7,0,0.05,0.3,0,10000,1);

  obstacles[1] = new Quadrilateral(90,9.7,6.3,0,0.5,5,0,0.05,0.3,0,10000,1);
  obstacles[2] = new Quadrilateral(90,7.7,3.3,0,0.5,2,0,0.05,0.3,0,10000,1);
  obstacles[3] = new Quadrilateral(0,7.4,0,0,0.3,3.5,0,0.05,0.3,0,10000,1);
  obstacles[4] = new Quadrilateral(180,5.2,6.6,0,0.3,2,0,0.05,0.3,0,10000,1);

  obstacles[5] = new Quadrilateral(90,10,-0.5,0,1,19.5,0,0.05,0.3,0,10000,1);

  for(int i=0;i<5;i++){

  vector<pair<float,float> > vert = obstacles[i]->get4Vertices();
    int ind=0;
    TR(vert,it){
     //output2((*it).F,(*it).S);
      borders[i][ind] = new Circle(360,0,0,0,0,(*it).F,(*it).S,0,0.05,0,0);

      ind++;
    }
  }

    //Boundaries

    //for(int i=0;i<STATIC_OBSTACLES;i++){
  
  /* vector<pair<float,float> > vertic;
      for(int j=0;j<4;j++){
        vertic.clear();
        vertic=obstacles[2]->setBoundaryPoints(vertic[j%4].F,vertic[j%4].S,vertic[(j+1)%4].F,vertic[(j+1)%4].S);
       }
       ATTEMPT = SZ(vertic);
       output1(ATTEMPT);*/
     /*int ind=0;
       TR(vertic,it){
        attempt[ind] = new Circle(360,0,0,0,0,(*it).F,(*it).S,0,0.05,0,0);
        ind++;
       }*/
    //}

    //**** 
   
    canon = new Quadrilateral(-50,-6.8,0.8,0,0.5,2.7,0,0.05,0.2,0,10000,1);
    base = new Quadrilateral(0,-6.8,0,0,2.5,0.8,0,0.05,0.2,0,10000,1);

    button_base = new Quadrilateral(0,5.9,1.3,0,0.3,1,0,0.05,1,0,10000,1);
    button = new Quadrilateral(0,5.55,1.3,0,0.35,0.8,0,0.05,1,0,10000,1);

    tar = new Quadrilateral(90,9.5,1.3,0,0.4,1.5,0,0.05,0.2,0,10000,1);

    lines[0] = new Line(9.2,0,0,90,1);
    lines[1] = new Line(8.2,0,0,49,1.45);
    lines[2] = new Line(9.2,0,0,39,1.45);

    lines[3] = new Line(8.9,0,0,49,1.36);
    lines[4] = new Line(9.2,0,0,49,1.36);
    lines[5] = new Line(8.6,0,0,49,1.36);

     lines[6] = new Line(8.4,0,0,39,1.36);
     lines[7] = new Line(8.7,0,0,39,1.36);
     lines[8] = new Line(9.0,0,0,39,1.36);


      for(int i=0;i<=10;i++){
        bar[i] = new Quadrilateral(0,-9+float(i)/8,8,0,0.25,1,0,0,1,0,0,1); 
      }

    /*lines[5] = new Line(8.6,-3,0,39,1.45);
    lines[6] = new Line(8.2,-3,0,39,1.45);*/

    /***
    boundary_bottom = new Quadrilateral(0,-4,-4,0,8,0.2,0,0.05,0.9,0,10000,1);
   // boundary_top = new Quadrilateral(0,-4,3.8,0,8,0.2,0.1);
    //boundary_left = new Quadrilateral(0,3.8,-4,0,0.2,8,0.1);
    boundary_right = new Quadrilateral(0,-4.1,-4,0,0.2,8,0,0.05,0.2,0,10000,1);
    
    ****/
    /*****/
    
/**


    hinge = new Circle(360,0,0,0,0,1.65,3.8,0,0.05,0,0);

    
    
*****/
/***** background elements****/

      back_floor = new Quadrilateral(0,0,0,0,6,5,0,0.05,0.3,0,10000,1);

      back_lines[0] = new Quadrilateral(0,0,0,0,5,5,0,0.05,0.3,0,10000,1);
      //back_lines[1] = new Quadrilateral(0,0,0,0,5,5,0,0.05,0.3,0,10000,1);

      paint[0] = new Line(-9.3,2,0,-5,4);
      paint[1] = new Line(-9.7,-2,0,5,4);
      paint[2] = new Line(-5.8,-1.33,0,40,2.7);

      paint[3] = new Line(6.2,1.35,0,185,4);
      paint[4] = new Line(6.2,-1.35,0,175,4);
      paint[5] = new Line(6.2,-1.33,0,45,2.7);

      back_circles[0] = new Circle(360,0,0,0,0,-5.6,0.0,0,1.35,0,0,0);
      back_circles[1] = new Circle(360,0,0,0,0,0,0,0,1.35,0,0,1);
      back_circles[2] = new Circle(360,0,0,0,0,-8,0,0,4,0,0,0);
      back_circles[3] = new Circle(360,0,0,0,0,6.2,0,0,1.35,0,0,0);
      back_circles[4] = new Circle(360,0,0,0,0,8.5,0,0,4,0,0,0);

    GLFWwindow* window = initGLFW(width, height);
	  initGL (window, width, height);
    double last_update_time = glfwGetTime(), current_time;
    double start_time=last_update_time;
    // Draw in loop
    pair <float,float> centre;float rad;
/*
    boundary_right->setBoundaryPoints(boundary_right->getX()+boundary_right->getSideX(),boundary_right->getY()+boundary_right->getSideY(),boundary_right->getX()+boundary_right->getSideX(),boundary_right->getY());
    for(int i=0;i<STATIC_OBSTACLES-1;i++){
     setBoundaries(obstacles[i]);
    }*/

    //*/*setBoundaries(button);
    //**setBoundaries(button_base);

    vector<pair<float,float> > verti;

    
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
/**** 
        if(motion_phase_projectile && projectile->getY()>4){
           projectile->setY(6);
          motion_phase_projectile = false;
        }

        if(motion_phase_projectile &&  projectile->getVY()==0 && projectile->getVX()==0 && projectile->getAX()==0 && projectile->getAY()==0){
          //projectile->setX(6);
         // double start_wait = glfwGetTime();
         
          //motion_phase_projectile = false;
        }
****/
        
        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
        if ((current_time - last_update_time) >= 0.05) { 

          if(!stop_oscillation){
            
            obstacles[4]->updateAngle(theta,-25,25);
            if(obstacles[4]->getAngle()>=obstacles[4]->rect_rot + 23 || obstacles[4]->getAngle()<=obstacles[4]->rect_rot -23)
              theta*=-1;
            verti.clear();
            verti = obstacles[4]->get4Vertices();
            int indi=0;
            TR(verti,it){
              //output2(SZ(verti),indi);
              //output2((*it).F,(*it).S);
              borders[4][indi]->updatePosition((*it).F,(*it).S);
              indi++;
            }
            
        }


        if(motion_phase_projectile){
              projectile->updatePosition(current_time-motion_start_time);
        }
//borders[4][1]->updatePosition(1);            
        // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
/***
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

          if(bound && obstacles[4]->getAngle()<=90){
            //output1(SZ(obstacles[4]->boundary_points));
            setBoundaries(obstacles[4]);
          }
          if(motion_phase_projectile && checkCollision(*projectile,*boundary_right,&centre,&rad)){
            onCollision(projectile,boundary_right,centre,rad);
          }

          if(motion_phase_projectile && checkCollision(*projectile,*button_base,&centre,&rad)){
            onCollision(projectile,button_base,centre,rad);
          }

          if(motion_phase_projectile && checkCollision(*projectile,*button,&centre,&rad)){
            onCollision(projectile,button,centre,rad);
            stop_oscillation=true;
          }


            
            for(int i=0;i<STATIC_OBSTACLES;i++){
              if(motion_phase_projectile && checkCollision(*projectile,*obstacles[i],&centre,&rad)){
                onCollision(projectile,obstacles[i],centre,rad);
                //output1(i);
                //output2(centre.F,centre.S);
               }
            }
            
            if(!stop_oscillation){
            if(obstacles[4]->getAngle()>=23 || obstacles[4]->getAngle()<=-23)
              theta*=-1;
            obstacles[4]->updateAngle(theta,-25,25);
            
            }
            else{
              //while(obstacles[4]->getAngle()!=180){
              if(obstacles[4]->getAngle()<=180){
                //output1(obstacles[4]->getAngle());
                obstacles[4]->updateAngle(2*theta,-25,180);
                
                if(obstacles[4]->getAngle() <=0)
                  theta = 1;
               //obstacles[4]->setY(3.6);
              }else{
                obstacles[4]->setAngle(181);
                bound = false;
                obstacles[4]->boundary_points.clear();
                if(bound1){
                  bound1=false;
                }
              }
            }
            if(motion_phase_projectile)
           // output2(projectile->getX(),projectile->getY());
            if(stop_oscillation){
              float dt = distance(tar->getX()+tar->getSideX()/2,tar->getY()+tar->getSideY()/2,projectile->getX(),projectile->getY());
              if(dt<=projectile->getRadius() + 0.5 && projectile->getX()>=2.8 && projectile->getX()<=3.5){
                projectile->setX(3.2);
                projectile->setY(-2.8);
                projectile->setVX(0);
                projectile->setVY(0);
                projectile->setAX(0);
                projectile->setAY(0);

              }
            }****/
            last_update_time = current_time;
        }
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
