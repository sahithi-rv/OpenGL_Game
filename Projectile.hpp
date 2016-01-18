#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "utility.hpp"

class Projectile{

	 	GLfloat* vertex_buffer;
	 	GLfloat* color_buffer;
	public:
		VAO  *rectangle;
		Projectile(){
			
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
};

#endif
