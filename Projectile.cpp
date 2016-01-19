#include "utility.h"


		Projectile::Projectile(float vx,float vy,float dx,float dy,float x,float y){
			gravity = vy;
			ax=0;
			v_x = dx;
			v_y = dy;
			s_x=x;
			s_y=y;
		}

		 void Projectile::setInitVertices( GLfloat vertex_buffer_data[]){
			vertex_buffer== new GLfloat[100];
			vertex_buffer=vertex_buffer_data;
		}

		void Projectile::setInitColors( GLfloat color_buffer_data[]){
			color_buffer== new GLfloat[100];
			color_buffer=color_buffer_data;
		}

		// Creates the rectangle object used in this sample code
		void Projectile::createRectangle ()
		{
			// GL3 accepts only Triangles. Quads are not supported
			
			GLfloat *vertex_buffer_data = new GLfloat[100];
			vertex_buffer_data= vertex_buffer;

			GLfloat *color_buffer_data = new GLfloat[100];
			color_buffer_data  = color_buffer;

			// create3DObject creates and returns a handle to a VAO that can be used later
			rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
		}

		void Projectile::renderProjectile(){
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

  			glm::mat4 translateRectangle = glm::translate (glm::vec3(this->s_x,this->s_y, 0));        // glTranslatef
 			// glm::mat4 rotateRectangle = glm::rotate((float)(projectile.rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  			Matrices.model *= (translateRectangle );//* rotateRectangle);
  			MVP = VP * Matrices.model;
  			glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  		}

  		void Projectile::updatePosition(double time){
  			this->s_x+=this->v_x + this->ax*time;
  			this->s_y+= this->v_y + this->gravity*time;
  			this->v_y+=this->gravity*time;
  		}
