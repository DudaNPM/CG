#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "ponto.h"
#include "vbo.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/glut.h"
#endif

#include "catmullrom.h"

using namespace std;

class Camera {
	private:
		int x_pos, y_pos, z_pos;
		int  x_la,  y_la,  z_la;
		int  x_up,  y_up,  z_up;
		int   fov,  near,   far;
	public:
		Camera();
		int getXPos();
		int getYPos();
		int getZPos();
		int	getXLa();
		int getYLa();
		int getZLa();
		int getXUp();
		int getYUp();
		int getZUp();
		int getFov();
		int getNear();
		int getFar();
		void setValues(int x_pos, int y_pos, int z_pos,
					   int  x_la, int  y_la, int  z_la,
					   int  x_up, int  y_up, int  z_up,
					   int   fov, int  near, int   far);
};


class Model {
	private:
		VBO* vbo;
		vector<Ponto> pontos;
	public:
		Model(vector<Ponto> pontos);
		void buildAxis();
		void draw(bool eixos);
		void drawVBO(bool eixos);
};

class Translate {
	private:
		float x, y, z;
		Catmullrom* c;
	public:
		Translate(float x, float y, float z);
		Translate(vector<Ponto> p, float time, bool align);
		void run(bool curves, bool stop);
};

class Rotate {
	private:
		bool rotate;
		float angulo, x, y, z;
		float timePast;
	public:
		Rotate(bool rotate, float angulo, float x, float y, float z);
		void run(bool stop);
};

class Scale {
	private:
		float x, y, z;
	public:
		Scale(float x, float y, float z);
		void run();
};

class Transform {
	private:
		Translate* translate;
		Rotate* rotate;
		Scale* scale;
	public:
		Transform();
		void setTranslate(Translate* t);
		void setRotate(Rotate* r);
		void setScale(Scale* s);
		void run(bool curves, bool stop);
};

class Group {
	private:
		vector<Transform*> transforms;
		vector<Model*> models;
		vector<Group*> subgroups;
	public:
		Group();
		void addModel(Model* m);
		void addTransform(Transform* t);
		void addSubGroup(Group* sub);
		void draw(bool vbo, bool eixos, bool curves, bool stop);
};