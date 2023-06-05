#include "transformations.h"


// CLASS CAMERA //

Camera::Camera() {
	this->x_pos = 0; this->x_la = 0; this->x_up = 0; this->fov = 0;
	this->y_pos = 0; this->y_la = 0; this->y_up = 0; this->near = 0;
	this->z_pos = 0; this->z_la = 0; this->z_up = 0; this->far = 0;
}

float Camera::getXPos() {return this->x_pos;}
float Camera::getYPos() {return this->y_pos;}
float Camera::getZPos() {return this->z_pos;}
float Camera::getXLa()  {return this->x_la;}
float Camera::getYLa()  {return this->y_la;}
float Camera::getZLa()  {return this->z_la;}
float Camera::getXUp()  {return this->x_up;}
float Camera::getYUp()  {return this->y_up;}
float Camera::getZUp()  {return this->z_up;}
float Camera::getFov()  {return this->fov;}
float Camera::getNear() {return this->near;}
float Camera::getFar()  {return this->far;}

void Camera::setValues(float x_pos, float y_pos, float z_pos,
	float  x_la, float  y_la, float  z_la,
	float  x_up, float  y_up, float  z_up,
	float   fov, float  near, float   far) {
	this->x_pos = x_pos; this->x_la = x_la; this->x_up = x_up; this->fov = fov;
	this->y_pos = y_pos; this->y_la = y_la; this->y_up = y_up; this->near = near;
	this->z_pos = z_pos; this->z_la = z_la; this->z_up = z_up; this->far = far;
}


// CLASS MODEL //

Model::Model(vector<Ponto> pontos, float* diffuse, float *ambient, float *specular, float *emissive, float shininess) {
	this->vbo = new VBO(pontos, false);
    this->pontos = pontos;
	this->diffuse = diffuse;
	this->ambient = ambient;
	this->specular = specular;
	this->emissive = emissive;
	this->shininess = shininess;
	this->texture = "";
	this->texid = -1;
}

Model::Model(vector<Ponto> pontos, float* diffuse, float* ambient, float* specular, float* emissive, float shininess, string texture) {
	this->vbo = new VBO(pontos, true);
	this->pontos = pontos;
	this->diffuse = diffuse;
	this->ambient = ambient;
	this->specular = specular;
	this->emissive = emissive;
	this->shininess = shininess;
	this->texture = texture;
	this->texid = loadTexture();
}

void Model::buildAxis() {
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -2.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -2.0f);
	glVertex3f(0.0f, 0.0f, 2.0f);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
}

void Model::draw(bool eixos) {
    Ponto p1, p2, p3;
    int size = this->pontos.size();

	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < size; i += 3) {

		p1 = this->pontos.at(i + 0);
		p2 = this->pontos.at(i + 1);
		p3 = this->pontos.at(i + 2);

		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
	}
	glEnd();
	glDisable(GL_COLOR_MATERIAL);

	if (eixos) this->buildAxis();
}


void Model::drawVBO(bool eixos) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, this->emissive);
	glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);

	this->vbo->draw(this->texid);
	if (eixos) this->buildAxis();
}


int Model::loadTexture() {
	unsigned int t, tw, th;
	unsigned char* texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)this->texture.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	return texID;
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