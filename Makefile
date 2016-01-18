all: Projectile2D

#sample2D: Sample_GL3_2D.cpp glad.c
#	g++ -o sample2D Sample_GL3_2D.cpp glad.c -lGL -lglfw -ldl

Projectile2D: Projectile1.cpp glad.c
	g++ -o Projectile2D Projectile1.cpp glad.c -lGL -lglfw -ldl

clean:
	rm Projectile2D #sample3D
