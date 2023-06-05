#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include "./tinyxml2/tinyxml2.h"
#include "transformations.h"
#include "ponto.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/glut.h"
#endif

using namespace std;
using namespace tinyxml2;

vector<Ponto> modelReader(string f);
void parseCamera(XMLElement* camera, Camera* c);
void parseModels(XMLElement* models, Group* group);
void parseTranslate(XMLElement* t, Transform* transform);
void parseRotate(XMLElement* t, Transform* transform);
void parseTransform(XMLElement* transform, Group* group);
void parseGroup(XMLElement* group, Group* grupo);
void xmlReader(string f, Camera* camera, vector<Group>* groups);