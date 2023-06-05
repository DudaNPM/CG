#include <vector>

#include "ponto.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define TESSELATION 100.0;
static float prev_y[3] = { 0,1,0 };

using namespace std;

class Catmullrom {
private:
	int pointCount;
	vector<Ponto> p;
	float time;
	bool align;
	float t, timePast;
	float pos[3];
	float deriv[3];
public:
	void buildRotMatrix(float* x, float* y, float* z, float* m);
	void cross(float* a, float* b, float* res);
	void normalize(float* a);
	void multMatrixVector(float* m, float* v, float* res);
	void getCatmullRomPoint(float t, Ponto p0, Ponto p1, Ponto p2, Ponto p3, float* pos, float* deriv);
	void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv);
	Catmullrom(vector<Ponto> p, float time, bool align);
	void renderCatmullRomCurve();
	void runCatmullRomCurve(bool curves, bool stop);
};