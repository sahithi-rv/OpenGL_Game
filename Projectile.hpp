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
		double mass;
		int fill;
		VAO  *rectangle;
		Projectile(float vx,float vy,float dx,float dy,float x,float y,float sdX,float sdY,double m,int filled){
			gravity = vy;
			ax=0;
			v_x = dx;
			v_y = dy;
			s_x=x;
			s_y=y;
			sideX=sdX;
			sideY=sdY;
			mass = m;
			
		}



		void setInitVertices( GLfloat vertex_buffer_data[]){
			vertex_buffer= new GLfloat[100];
			vertex_buffer=vertex_buffer_data;
		}

		void setInitColors( GLfloat color_buffer_data[]){
			color_buffer=new GLfloat[100];
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

  		
};

class Quadrilateral{

public:

	GLfloat* vertex_buffer;
	GLfloat* color_buffer;


	VAO  *rectangle;
	float rectangle_rotation;
	float vx,vy,vz;
	float sideX,sideY,sideZ;
	float boundary_radius,cor,force;
	vector<pair<float,float> > boundary_points;
	double mass;int fill;
	Quadrilateral(float rot,float v_x,float v_y,float v_z,float sdX,float sdY,float sdZ,float rad,float COR,float NF,double m,int filled ){
		rectangle_rotation=rot;
		vx=v_x;
		vy=v_y;
		vz=v_z;
		sideX=sdX;
		sideY=sdY;
		sideZ=sdZ;
		boundary_radius = rad;
		cor = COR;
		force = NF;
		mass = m;
		fill = filled;
	}

	float getX(){ return vx ;}

	float getY(){ return vy ;}
	float getZ(){ return vz ;}

	float getSideZ(){
		return sideZ;
	}


	float getSideX(){
		return sideX;
	}

	float getSideY(){
		return sideY;
	}

	float getAngle(){
		return rectangle_rotation;
	}

	float getNF(){
		return force;
	}
	void setNF(float NF){
		force = NF;
	}
	GLfloat * getInitVertices(){
		//output2(vx,vy);
		//output2(sideX,sideY);
		/**GLfloat  vertex_buffer_data[] = {
			0,0,0,
			0,0+sideY,0,
			0+sideX,0+sideY,0,

			0+sideX,0+sideY,0,
			0+sideX,0,0,
			0,0,0
		};**/
		GLfloat * vertex_buffer_data = new GLfloat[100];
		vertex_buffer_data[0]=0;
		vertex_buffer_data[1]=0;
		vertex_buffer_data[2]=0;
		vertex_buffer_data[3]=0;
		vertex_buffer_data[4]=0+sideY;
		vertex_buffer_data[5]=0;
		vertex_buffer_data[6]=0+sideX;
		vertex_buffer_data[7]=0+sideY;
		vertex_buffer_data[8]=0+sideZ;
		vertex_buffer_data[9]=0+sideX;
		vertex_buffer_data[10]=0+sideY;
		vertex_buffer_data[11]=0+sideZ;
		vertex_buffer_data[12]=0+sideX;
		vertex_buffer_data[13]=0;
		vertex_buffer_data[14]=0+sideZ;
		vertex_buffer_data[15]=0;
		vertex_buffer_data[16]=0;
		vertex_buffer_data[17]=0;		
		vertex_buffer = new GLfloat[100];
		return vertex_buffer = vertex_buffer_data;
	}
	GLfloat * getInitColors(float r,float g,float b){
		
		GLfloat * color_buffer_data = new GLfloat[100];
		for (int i=0; i<6; i++) {
        	color_buffer_data [3*i] = r;
        	color_buffer_data [3*i + 1] = g;
        	color_buffer_data [3*i + 2] = b;
   	    }
		color_buffer = new GLfloat[100];
		return color_buffer = color_buffer_data;
	}

	void setInitVertices(GLfloat vertex_buffer_data[] ){
		//vertex_buffer = new GLfloat[100];
		vertex_buffer = vertex_buffer_data;
	}

	

	void setInitColors( GLfloat color_buffer_data[]){
		//color_buffer== new GLfloat[100];
		color_buffer=color_buffer_data;
	}

	void createRectangle ()
	{
			// GL3 accepts only Triangles. Quads are not supported
			
			GLfloat *vertex_buffer_data = new GLfloat[100];
			vertex_buffer_data= vertex_buffer;

			GLfloat *color_buffer_data = new GLfloat[100];
			color_buffer_data  = color_buffer;
			//if(fill)
				rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
			//else
			//	rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_LINE);
	}

	void renderQuad(){
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

  	void setBoundaryPoints(float x1,float y1, float x2,float y2){

  		float x,y;
  		double angle = atan2( (y2-y1),(x2-x1) );
  		float r = boundary_radius;
  		float dt = distance(x1,y1,x2,y2);
  		
  		while (r <= dt+0.2){
  			x = x1 + r * cos(angle);
  			y = y1 + r * sin(angle);
  			boundary_points.PB(MP(x,y));
  			r += boundary_radius/16;
  		}
  	}

	void updateAngle(float theta,float mini,float maxi){
		rectangle_rotation += theta;
		if(rectangle_rotation>=maxi || rectangle_rotation<=mini)
			rectangle_rotation -= theta;
	
	}

	void updatePosition(float dx){
		vx+=dx;
		if(getX() < -4 || getX() > -2)
			vx-=dx;
	}



};

class Circle{

public:
	GLfloat* vertex_buffer;
	GLfloat* color_buffer;
	VAO * circle;
	int num_vertices;
	float cx,cy,cz,radius;
	float gravity ;
	float ax;
	float v_x;
	float v_y;
	float s_x;
	float s_y;
	float ext_force_x,ext_force_y;
    Circle(int num,float vx,float vy,float dx,float dy,float c_x,float c_y,float c_z,float r,float EFX,float EFY){
			gravity = vy;
			ax=vx;
			v_x = dx;
			v_y = dy;
			num_vertices = num;
			radius = r;
			cx = c_x;
			cy = c_y;
			cz = c_z;
			ext_force_x= EFX;
			ext_force_y = EFY;
	}

		float getX(){ return cx ;}

		float getY(){ return cy ;}

		void setX(float dx){
			cx=dx;
		}
		void setY(float dy){
			cy=dy;
		}

		float getRadius(){
			return radius;
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
		float getAX(){
			return ax;
		}
		float getAY(){
			return gravity;
		}

		void setAX(float dx){
			ax=dx;
		}
		void setAY(float dy){
			gravity=dy;
		}

		float getEFX(){
			return ext_force_x;
		}

		void setEFX(float EF){
			ext_force_x = EF;
		}

		float getEFY(){
			return ext_force_y;
		}

		void setEFY(float EFY){
			ext_force_y = EFY;
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

	void renderCircle(){
		glm::mat4 MVP;	// MVP = Projection * View * Model
		Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  		glm::mat4 VP = Matrices.projection * Matrices.view;
  			/* Render your scene */

  		Matrices.model = glm::mat4(1.0f);



  		
  		glm::mat4 translateCircle = glm::translate (glm::vec3(cx,cy,cz));        // glTranslatef
 	   // glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f*-1), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  		Matrices.model *= translateCircle;//*((rotateRectangle ));
  		MVP = VP * Matrices.model;
  		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  	}

  	void updatePosition(double time){
  		//output1(ax);
  			cx+=v_x + ax*time;
  			cy+= v_y + gravity*time;
  			v_y+=gravity*time;
  			v_x+=ax*time;
  	}


};

#endif
