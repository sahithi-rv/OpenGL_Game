all: Projectile1

#sample2D: Sample_GL3_2D.cpp glad.c
#	g++ -o sample2D Sample_GL3_2D.cpp glad.c -lGL -lglfw -ldl

#Projectile1: Projectile1.cpp glad.c
#	g++ -o Projectile1 Projectile1.cpp glad.c -lGL -lglfw -ldl

#clean:
#	rm Projectile2D #sample3D

CC = g++
CFLAGS = -lGL -lglfw -ldl

BIN = Projectile1
OBJS = Projectile1.o

$(BIN):: $(OBJS)
	$(CC) -o $(BIN) $(OBJS) glad.c $(CFLAGS)

Projectile1.o::utility.hpp Projectile.hpp

clean::
	/bin/rm -f *~ *.o