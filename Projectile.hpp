#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "utility.hpp"

class Projectile{

	 	GLfloat* vertex_buffer;
	 	GLfloat* color_buffer;
	public:
		float gravity ;
		float ax;
		float v_x;
		float v_y;
		float s_x;
		float s_y;
		float sideX,sideY;
		VAO  *rectangle;
		Projectile(float vx,float vy,float dx,float dy,float x,float y,float sdX,float sdY){
			gravity = vy;
			ax=0;
			v_x = dx;
			v_y = dy;
			s_x=x;
			s_y=y;
			sideX=sdX;
			sideY=sdY;

		}

		float getX(){ return s_x ;}

		float getY(){ return s_y ;}

		float getSideX(){
			return sideX;
		}

		float getSideY(){
			return sideY;
		}

		float getVX(){
			return v_x;
		}
		float getVY(){
			return v_y;
		}

		void setVX(float dx){
			v_x=dx;
		}
		void setVY(float dy){
			v_y=dy;
		}

		void setInitVertices( GLfloat vertex_buffer_data[]){
			vertex_buffer== new GLfloat[100];
			vertex_buffer=vertex_buffer_data;
		}

		void setInitColors( GLfloat color_buffer_data[]){
			color_buffer== new GLfloat[100];
			color_buffer=color_buffer_data;
		}

		// Creates the rectangle object used in this sample code
		void createRectangle ()
		{
			// GL3 accepts only Triangles. Quads are not supported
			
			GLfloat *vertex_buffer_data = new GLfloat[100];
			vertex_buffer_data= vertex_buffer;

			GLfloat *color_buffer_data = new GLfloat[100];
			color_buffer_data  = color_buffer;

			// create3DObject creates and returns a handle to a VAO that can be used later
			rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
		}

		void renderProjectile(){
			glm::mat4 MVP;	// MVP = Projection * View * Model

			// Compute Camera matrix (view)
  			// Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
  			//  Don't change unless you are sure!!
  			Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  			// Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
  			//  Don't change unless you are sure!!
  			glm::mat4 VP = Matrices.projection * Matrices.view;
  			/* Render your scene */

  			// Pop matrix to undo transformations till last push matrix instead of recomputing model matrix
  			// glPopMatrix ();
  			Matrices.model = glm::mat4(1.0f);

  			glm::mat4 translateRectangle = glm::translate (glm::vec3(s_x,s_y, 0));        // glTranslatef
 			// glm::mat4 rotateRectangle = glm::rotate((float)(projectile.rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  			Matrices.model *= (translateRectangle );//* rotateRectangle);
  			MVP = VP * Matrices.model;
  			glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  		}

  		void updatePosition(double time){
  			s_x+=v_x + ax*time;
  			s_y+= v_y + gravity*time;
  			v_y+=gravity*time;
  		}
};

class Canon{

public:

	GLfloat* vertex_buffer;
	GLfloat* color_buffer;


	VAO  *rectangle;
	float rectangle_rotation;
	float vx,vy,vz;
	float sideX,sideY;

	Canon(float rot,float v_x,float v_y,float v_z,float sdX,float sdY){
		rectangle_rotation=rot;
		vx=v_x;
		vy=v_y;
		vz=v_z;
		sideX=sdX;
		sideY=sdY;
	}

	float getX(){ return vx ;}

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

class Obstacle{

public:
	GLfloat* vertex_buffer;
	GLfloat* color_buffer;
	VAO * circle;
	int num_vertices;
	float cx,cy,cz,radius;
	Obstacle(int num,float c_x,float c_y,float c_z,float r){
		num_vertices = num;
		radius = r;
		cx = c_x;
		cy = c_y;
		cz = c_z;
	}
	void setInitVertices( GLfloat vertex_buffer_data[]){
		vertex_buffer = new GLfloat[num_vertices];
		vertex_buffer = vertex_buffer_data;
	}

	

	void setInitColors( GLfloat color_buffer_data[]){
		color_buffer== new GLfloat[num_vertices];
		color_buffer=color_buffer_data;
	}

	void createCircle(){
			
		circle = create3DObject(GL_TRIANGLE_FAN,num_vertices,vertex_buffer,color_buffer,GL_FILL);
	}

	void renderObstacle(){
		glm::mat4 MVP;	// MVP = Projection * View * Model
		Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  		glm::mat4 VP = Matrices.projection * Matrices.view;
  			/* Render your scene */

  		Matrices.model = glm::mat4(1.0f);



  		glm::mat4 translateCircle = glm::translate (glm::vec3(0,0,0));        // glTranslatef
 	   // glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f*-1), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  		Matrices.model *= translateCircle;//*((rotateRectangle ));
  		MVP = VP * Matrices.model;
  		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  	}


};

#endif
