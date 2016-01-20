class Canon{

public:

	GLfloat* vertex_buffer;
	GLfloat* color_buffer;


	VAO  *rectangle;
	float rectangle_rotation;
	float vx,vy,vz;
	float sideX,sideY;

	Canon(float rot,float v_x,float v_y,float v_z,float sdX,float sdY);

	float getX();
	float getY(){ return vy ;}

	float getSideX(){
		return sideX;
	}

	float getSideY(){
		return sideY;
	}

	void setInitVertices( GLfloat vertex_buffer_data[]){
		vertex_buffer = new GLfloat[100];
		vertex_buffer = vertex_buffer_data;
	}

	

	void setInitColors( GLfloat color_buffer_data[]){
		color_buffer== new GLfloat[100];
		color_buffer=color_buffer_data;
	}

	void createRectangle ()
	{
			// GL3 accepts only Triangles. Quads are not supported
			
			GLfloat *vertex_buffer_data = new GLfloat[100];
			vertex_buffer_data= vertex_buffer;

			GLfloat *color_buffer_data = new GLfloat[100];
			color_buffer_data  = color_buffer;

			// create3DObject creates and returns a handle to a VAO that can be used later
			rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
			//base = create3DObject(GL_TRIANGLES,6,base_vertex_buffer,color_buffer,GL_FILL);
	}

	void renderCanon(){
		glm::mat4 MVP;	// MVP = Projection * View * Model
		Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  		glm::mat4 VP = Matrices.projection * Matrices.view;
  			/* Render your scene */

  		Matrices.model = glm::mat4(1.0f);



  		glm::mat4 translateRectangle = glm::translate (glm::vec3(vx,vy,vz));        // glTranslatef
 	    glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f*-1), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  		Matrices.model *= translateRectangle*((rotateRectangle ));
  		MVP = VP * Matrices.model;
  		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  	}

	void updateAngle(){
		if(rectangle_rotation<=90)
			rectangle_rotation+=1;
	
	}

};