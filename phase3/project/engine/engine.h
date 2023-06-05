#include <iostream>
#include <fstream>
#include <vector>
#include "./tinyxml2/tinyxml2.h"
#include "transformations.h"
#include "xmlreader.h"
#include "ponto.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include "GL/glut.h"
#endif

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace tinyxml2;