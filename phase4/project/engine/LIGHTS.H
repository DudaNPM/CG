#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Light {
public:
	GLenum i;
	float* diffuse;
	float* ambient;
	float* specular;
	Light(GLenum i);
	Light(GLenum i, float* diffuse, float* ambient, float* specular);
	void init();
	virtual void apply();
};

class PointLight : public Light {
public:
	float* position;
	float quad_att;
	PointLight(GLenum i, float* pos, float quad_att);
	PointLight(GLenum i, float* diffuse, float* ambient, float* specular, float* pos, float quad_att);
	void apply();
};

class DirectionalLight : public Light {
public:
	float* direction;
	DirectionalLight(GLenum i, float* dir);
	DirectionalLight(GLenum i, float* diffuse, float* ambient, float* specular, float* dir);
	void apply();
};

class SpotLight : public Light {
public:
	float* position;
	float* direction;
	float cutoff;
	float exponent;
	SpotLight(GLenum i, float* pos, float* dir, float cutoff, float exponent);
	SpotLight(GLenum i, float* diffuse, float* ambient, float* specular, float* pos, float* dir, float cutoff, float exponent);
	void apply();
};
