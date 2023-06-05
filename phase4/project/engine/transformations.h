#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <IL/il.h>

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
		float x_pos, y_pos, z_pos;
		float  x_la,  y_la,  z_la;
		float  x_up,  y_up,  z_up;
		float   fov,  near,   far;
	public:
		Camera();
		float getXPos();
		float getYPos();
		float getZPos();
		float	getXLa();
		float getYLa();
		float getZLa();
		float getXUp();
		float getYUp();
		float getZUp();
		float getFov();
		float getNear();
		float getFar();
		void setValues(float x_pos, float y_pos, float z_pos,
			float  x_la, float  y_la, float  z_la,
			float  x_up, float  y_up, float  z_up,
			float   fov, float  near, float   far);
};


class Model {
	private:
		VBO* vbo;
		vector<Ponto> pontos;
		float* diffuse, * ambient, * specular, * emissive;
		float shininess;
		string texture;
		int texid;
	public:
		Model(vector<Ponto> pontos, float* diffuse, float *ambient, float *specular, float *emissive, float shininess);
		Model(vector<Ponto> pontos, float* diffuse, float* ambient, float* specular, float* emissive, float shininess, string texture);
		void buildAxis();
		void draw(bool eixos);
		void drawVBO(bool eixos);
		int loadTexture();
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