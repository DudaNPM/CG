#include "catmullrom.h"


void Catmullrom::buildRotMatrix(float* x, float* y, float* z, float* m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void Catmullrom::cross(float* a, float* b, float* res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}


void Catmullrom::normalize(float* a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}


void Catmullrom::multMatrixVector(float* m, float* v, float* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}


void Catmullrom::getCatmullRomPoint(float t, Ponto p0, Ponto p1, Ponto p2, Ponto p3, float* pos, float* deriv) {

	// catmull-rom matrix
	float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f} };

	float px[4] = { p0.x, p1.x, p2.x, p3.x }; float ax[4];
	float py[4] = { p0.y, p1.y, p2.y, p3.y }; float ay[4];
	float pz[4] = { p0.z, p1.z, p2.z, p3.z }; float az[4];

	// Compute A = M * P
	multMatrixVector((float*)m, px, ax);
	multMatrixVector((float*)m, py, ay);
	multMatrixVector((float*)m, pz, az);

	// Compute pos = T * A
	pos[0] = powf(t, 3.0) * ax[0] + powf(t, 2.0) * ax[1] + t * ax[2] + ax[3];
	pos[1] = powf(t, 3.0) * ay[0] + powf(t, 2.0) * ay[1] + t * ay[2] + ay[3];
	pos[2] = powf(t, 3.0) * az[0] + powf(t, 2.0) * az[1] + t * az[2] + az[3];

	// compute deriv = T' * A
	deriv[0] = 3 * powf(t, 2.0) * ax[0] + 2 * t * ax[1] + ax[2];
	deriv[1] = 3 * powf(t, 2.0) * ay[0] + 2 * t * ay[1] + ay[2];
	deriv[2] = 3 * powf(t, 2.0) * az[0] + 2 * t * az[1] + az[2];
}


void Catmullrom::getGlobalCatmullRomPoint(float gt, float* pos, float* deriv) {
	float t = gt * this->pointCount; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + this->pointCount - 1) % this->pointCount;
	indices[1] = (indices[0] + 1) % this->pointCount;
	indices[2] = (indices[1] + 1) % this->pointCount;
	indices[3] = (indices[2] + 1) % this->pointCount;
	
	getCatmullRomPoint(t, this->p.at(indices[0]), this->p.at(indices[1]), this->p.at(indices[2]), this->p.at(indices[3]), pos, deriv);
}


Catmullrom::Catmullrom(vector<Ponto> p, float time, bool align) {
	this->pointCount = p.size();
	this->p = p;
	this->time = time * 1000;
	this->align = align;
	this->t = 0;
	this->timePast = 0;
}


void Catmullrom::renderCatmullRomCurve() {
	glBegin(GL_LINE_LOOP);
	float gt = 0;
	while (gt < 1) {
		getGlobalCatmullRomPoint(gt, this->pos, this->deriv);
		glVertex3f(this->pos[0], this->pos[1], this->pos[2]);
		gt += 1.0 / TESSELATION;
	}
	glEnd();
}


void Catmullrom::runCatmullRomCurve(bool curves, bool stop) {
	if (curves) renderCatmullRomCurve();

	getGlobalCatmullRomPoint(this->t, this->pos, this->deriv);

	glTranslatef(this->pos[0], this->pos[1], this->pos[2]);

	float x[3];
	if (this->align) {
		x[0] = this->deriv[0];
		x[1] = this->deriv[1];
		x[2] = this->deriv[2];
	} else {
		x[0] = 1;
		x[1] = 0;
		x[2] = 1;
	}
	normalize(x);

	float z[3];
	cross(x, prev_y, z);
	normalize(z);

	float y[3];
	cross(z, x, y);
	normalize(y);

	float m[16];
	buildRotMatrix(x, y, z, m);
	glMultMatrixf(m);
	
	int time = glutGet(GLUT_ELAPSED_TIME);
	int delta = time - this->timePast;
	this->timePast = time;

	this->t += (delta / this->time) * !stop;
}