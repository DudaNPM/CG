#include "transformations.h"


// CLASS CAMERA //

Camera::Camera() {
	this->x_pos = 0; this->x_la = 0; this->x_up = 0; this->fov = 0;
	this->y_pos = 0; this->y_la = 0; this->y_up = 0; this->near = 0;
	this->z_pos = 0; this->z_la = 0; this->z_up = 0; this->far = 0;
}

int Camera::getXPos() {return this->x_pos;}
int Camera::getYPos() {return this->y_pos;}
int Camera::getZPos() {return this->z_pos;}
int Camera::getXLa()  {return this->x_la;}
int Camera::getYLa()  {return this->y_la;}
int Camera::getZLa()  {return this->z_la;}
int Camera::getXUp()  {return this->x_up;}
int Camera::getYUp()  {return this->y_up;}
int Camera::getZUp()  {return this->z_up;}
int Camera::getFov()  {return this->fov;}
int Camera::getNear() {return this->near;}
int Camera::getFar()  {return this->far;}

void Camera::setValues(int x_pos, int y_pos, int z_pos,
					   int  x_la, int  y_la, int  z_la,
					   int  x_up, int  y_up, int  z_up,
					   int   fov, int  near, int   far) {
	this->x_pos = x_pos; this->x_la = x_la; this->x_up = x_up; this->fov = fov;
	this->y_pos = y_pos; this->y_la = y_la; this->y_up = y_up; this->near = near;
	this->z_pos = z_pos; this->z_la = z_la; this->z_up = z_up; this->far = far;
}


// CLASS MODEL //

Model::Model(vector<Ponto> pontos) {
	this->vbo = new VBO(pontos);
    this->pontos = pontos;
}

void Model::buildAxis() {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -2.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -2.0f);
	glVertex3f(0.0f, 0.0f, 2.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();
}

void Model::draw(bool eixos) {
    Ponto p1, p2, p3;
    int size = this->pontos.size();

	if (eixos) this->buildAxis();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < size; i += 3) {

		p1 = this->pontos.at(i + 0);
		p2 = this->pontos.at(i + 1);
		p3 = this->pontos.at(i + 2);

		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
	}
	glEnd();
}


void Model::drawVBO(bool eixos) {
	if (eixos) this->buildAxis();
	this->vbo->draw();
}


// CLASS TRANSLATE //

Translate::Translate(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->c = NULL;
}

Translate::Translate(vector<Ponto> p, float time, bool align) {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->c = new Catmullrom(p,time, align);
}

void Translate::run(bool curves, bool stop) {
	glTranslatef(this->x, this->y, this->z);
	if (c != NULL) this->c->runCatmullRomCurve(curves, stop);
}


// CLASS ROTATE //

Rotate::Rotate(bool rotate, float angulo, float x, float y, float z) {
	this->rotate = rotate;
	if (rotate) this->angulo = angulo * 1000;	// tempo de animação em milisegundos
	else this->angulo = angulo;
	this->x = x;
	this->y = y;
	this->z = z;
	this->timePast = 0;
}

void Rotate::run(bool stop) {
	if (this->rotate) {
		int time = glutGet(GLUT_ELAPSED_TIME);
		float delta = time - this->timePast;
		this->timePast = time;
		this->angulo += (360.0 / this->angulo) * delta * !stop;
	}
	glRotatef(this->angulo, this->x, this->y, this->z);
}


// CLASS SCALE //

Scale::Scale(float sx, float sy, float sz) {
	this->x = sx;
	this->y = sy;
	this->z = sz;
}

void Scale::run() {
	glScalef(this->x, this->y, this->z);
}


// CLASS TRANSFORM //

Transform::Transform() {
	this->translate = NULL;
	this->scale = NULL;
	this->rotate = NULL;
}

void Transform::setTranslate(Translate* translate) {
	this->translate = translate;
}

void Transform::setRotate(Rotate* rotate) {
	this->rotate = rotate;
}

void Transform::setScale(Scale* scale) {
	this->scale = scale;
}

void Transform::run(bool curves, bool stop) {
	if		(this->scale) this->scale->run();
	else if (this->rotate) this->rotate->run(stop);
	else if (this->translate) this->translate->run(curves, stop);
}


// CLASS GROUP //

Group::Group() {
	this->transforms = vector<Transform*>();
	this->models = vector<Model*>();
	this->subgroups = vector<Group*>();
}

void Group::addModel(Model* model) {
	this->models.push_back(model);
}

void Group::addSubGroup(Group* sub) {
	this->subgroups.push_back(sub);
}

void Group::addTransform(Transform* transform) {
	this->transforms.push_back(transform);
}

void Group::draw(bool vbo, bool eixos, bool curves, bool stop) {
	glPushMatrix();
	for (Transform* transform : this->transforms)
		transform->run(curves, stop);
	for (Model* model : this->models) {
		if (vbo) model->drawVBO(eixos);
		else model->draw(eixos);
	}
	for (Group* group : this->subgroups)
		group->draw(vbo, eixos, curves, stop);
	glPopMatrix();
}