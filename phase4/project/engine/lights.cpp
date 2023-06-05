#include "lights.h"

// Light

Light::Light(GLenum i) {
    float* difusa = (float*)malloc(sizeof(float) * 4);
    float* ambiente = (float*)malloc(sizeof(float) * 4);
    float* especular = (float*)malloc(sizeof(float) * 4);

    difusa[0] = 1.0f;
    difusa[1] = 1.0f;
    difusa[2] = 1.0f;
    difusa[3] = 1.0f;

    ambiente[0] = 0.2f;
    ambiente[1] = 0.2f;
    ambiente[2] = 0.2f;
    ambiente[3] = 1.0f;

    especular[0] = 1.0f;
    especular[1] = 1.0f;
    especular[2] = 1.0f;
    especular[3] = 1.0f;

    this->i = i;
    this->diffuse  = difusa;
    this->ambient  = ambiente;
    this->specular = especular;
}

Light::Light(GLenum i, float* diffuse, float* ambient, float* specular) {
    this->i = i;
    this->diffuse  = diffuse;
    this->ambient  = ambient;
    this->specular = specular;
}

void Light::init() {
    glEnable( GL_LIGHT0 + this->i);
    glLightfv(GL_LIGHT0 + this->i, GL_DIFFUSE, this->diffuse);
    glLightfv(GL_LIGHT0 + this->i, GL_AMBIENT, this->ambient);
    glLightfv(GL_LIGHT0 + this->i, GL_SPECULAR, this->specular);
}

void Light::apply() {}


// Point Light

PointLight::PointLight(GLenum i, float* pos, float quad_att) : Light(i) {
    this->position = pos;
    this->quad_att = quad_att;
    this->init();
}

PointLight::PointLight(GLenum i, float* diffuse, float* ambient, float* specular, float* pos, float quad_att) : Light(i, diffuse, ambient, specular) {
    this->position = pos;
    this->quad_att = quad_att;
    this->init();
}

void PointLight::apply() {
    glLightfv(GL_LIGHT0 + this->i, GL_POSITION, this->position);
    glLightfv(GL_LIGHT0 + this->i, GL_QUADRATIC_ATTENUATION, &(this->quad_att));
}


// Directional Light

DirectionalLight::DirectionalLight(GLenum i, float* dir) : Light(i) {
    this->direction = dir;
    this->init();
}

DirectionalLight::DirectionalLight(GLenum i, float* diffuse, float* ambient, float* specular, float* dir) : Light(i, diffuse, ambient, specular) {
    this->direction = dir;
    this->init();
}

void DirectionalLight::apply() {
    glLightfv(GL_LIGHT0 + this->i, GL_POSITION, this->direction);
}


// Spot Light

SpotLight::SpotLight(GLenum i, float* pos, float* dir, float cutoff, float exponent) : Light(i) {
    this->position = pos;
    this->direction = dir;
    this->cutoff = cutoff;
    this->exponent = exponent;
    this->init();
}

SpotLight::SpotLight(GLenum i, float* diffuse, float* ambient, float* specular, float* pos, float* dir, float cutoff, float exponent) : Light(i, diffuse, ambient, specular) {
    this->position = pos;
    this->direction = dir;
    this->cutoff = cutoff;
    this->exponent = exponent;
    this->init();
}

void SpotLight::apply() {
    glLightfv(GL_LIGHT0 + this->i, GL_POSITION, this->position);
    glLightfv(GL_LIGHT0 + this->i, GL_SPOT_DIRECTION, this->direction);
    glLightf( GL_LIGHT0 + this->i, GL_SPOT_CUTOFF, this->cutoff);
    glLightf( GL_LIGHT0 + this->i, GL_SPOT_EXPONENT, this->exponent);
}