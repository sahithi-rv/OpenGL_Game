#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "struct.h"


#define DISPLACEMENT 0.5
#define VELOCITY 0.15
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define GLM_FORCE_RADIANS
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define RI(a) scanf("%d",&a);
#define SZ(a) (int)(a.size())
#define SET(a,b) memset(a,b,sizeof(a))
#define TR(a,t) for(__typeof(a.begin()) t=a.begin();t!=a.end();t++)
#define rep(i,l,h) for(int i=(l); i<=(h);i++)
#define repd(i,h,l) for(int i=(h);i>=(l);i--)
#define ALL(a) a.begin(),a.end()
#define DRT()  int t; cin>>t; while(t--)
#define PRSNT(a,e) (a.find(e) != a.end())
#define MINH priority_queue<int, vector<int>, greater<int> >
#define N 100
#define MOD 1000000007
#define output1(x) cout << #x << " " << x << endl;
#define output2(x,y) cout <<x<<" "<<y <<endl;
#define inp1(x) cin >> x;
#define inp2(x,y) cin >> x >> y;
#define MAX(a,b) a>b?a:b
#define MIN(a,b) a<b?a:b

typedef long long int  ll;

using namespace std;



GLuint programID;

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
static void error_callback(int error, const char* description);
void quit(GLFWwindow *window);
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat* color_buffer_data, GLenum fill_mode);
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode);
void draw3DObject (struct VAO* vao);
void reshapeWindow (GLFWwindow* window, int width, int height);


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
		VAO  *rectangle;

		Projectile(float vx,float vy,float dx,float dy,float x,float y);
		
		void setInitVertices( GLfloat vertex_buffer_data[]);

		void setInitColors( GLfloat color_buffer_data[]);

		// Creates the rectangle object used in this sample code
		void createRectangle ();
		
		void renderProjectile();

  		void updatePosition(double time);
};


#endif