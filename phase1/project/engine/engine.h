#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/glut.h"
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include "./tinyxml2/tinyxml2.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace tinyxml2;

struct Ponto {
	float x;
	float y;
	float z;
};