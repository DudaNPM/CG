#include "engine.h"

// controladores extras: eixos, modo de apresentação
bool eixos = false;
bool polymode = false;

float calpha = 0.0f, cbeta = 0.0f;	// angulos da camara
float cdist = 0.0f;					// distancia da camara
float cx, cy, cz;					// camera position
float lx, ly, lz;					// lookAt point
float ux, uy, uz;					// up vector
float fov, near, far;				// projection

string path = "../ficheiros/";
vector<Ponto> pontos;


void spherical2Cartesian() {
	cx = cdist * cos(cbeta) * sin(calpha);
	cy = cdist * sin(cbeta);
	cz = cdist * cos(cbeta) * cos(calpha);
}


void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(fov, ratio, near, far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawObject() {
	Ponto p1, p2, p3;
	int size = pontos.size();

	float red = 1.0f, green = 1.0f, blue = 1.0f;

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < size; i += 6) {
		glColor3f(red, green, blue);

		p1 = pontos.at(i);
		p2 = pontos.at(i + 1);
		p3 = pontos.at(i + 2);

		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);

		p1 = pontos.at(i + 3);
		p2 = pontos.at(i + 4);
		p3 = pontos.at(i + 5);

		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);

		red = red - 0.01;
		green = green - 0.01;
		blue = blue - 0.01;
		// red = (float)rand() / (RAND_MAX);
		// green = (float)rand() / (RAND_MAX);
		// blue = (float)rand() / (RAND_MAX);
	}
	glEnd();
}


void buildExis() {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}


void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(cx, cy, cz,
			  lx, ly, lz,
			  ux, uy, uz);
	
	// draw instructions
	
	if (eixos) buildExis();

	// nao sei se sera o melhor sitio para isto...
	if (polymode) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	drawObject();
    
	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
	switch (c) {
	case 's':
		cdist = cdist + 0.5;
		break;
	case 'w':
		if (cdist > 0)
			cdist = cdist - 0.5;
		break;
	case 'z':
		if (eixos) eixos = false;
		else eixos = true;
		break;
	case 'x':
		if (polymode) polymode = false;
		else polymode = true;
		break;
	default:
		break;
	}

	spherical2Cartesian();
	glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		calpha = calpha - 0.05;
		break;
	case GLUT_KEY_LEFT:
		calpha = calpha + 0.05;
		break;
	case GLUT_KEY_UP:
		if (cbeta < M_PI_2 - 0.05)
			cbeta = cbeta + 0.05f;
		else cbeta = M_PI_2;
		break;
	case GLUT_KEY_DOWN:
		if (cbeta > -M_PI_2 + 0.05)
			cbeta = cbeta - 0.05f;
		else cbeta = -M_PI_2;
		break;
	default:
		break;
	}

	spherical2Cartesian();
	glutPostRedisplay();
}

void modelReader(string f) {
	ifstream file(f);
	Ponto p;
	if (file.is_open()) {
		while (file.good()) {
			file >> p.x >> p.y >> p.z;
			if(file.eof())
				break;
			pontos.push_back(p);
		}
	}
	else cout << "ERROR opening file " << f << endl;
	
	file.close();
}

void xmlReader(string f) {
	XMLDocument doc;
	XMLElement* root;

	if (!(doc.LoadFile(f.c_str()))) {
		root = doc.RootElement();

		XMLElement* elem = root->FirstChildElement();
		// camera settings
		if (elem != NULL) {
			XMLElement* settings = elem->FirstChildElement();

			// camera position
			if (settings != NULL) {
				cx = atof(settings->Attribute("x"));
				cy = atof(settings->Attribute("y"));
				cz = atof(settings->Attribute("z"));

				cbeta = atan(cy / (sqrt(pow(cx,2) + pow(cz,2))));
				cdist = cy / sin(cbeta);
				calpha = acos(cz / (cdist * cos(cbeta)));
			}

			settings = settings->NextSiblingElement();
			// lookAt point
			if (settings != NULL) {
				lx = atof(settings->Attribute("x"));
				ly = atof(settings->Attribute("y"));
				lz = atof(settings->Attribute("z"));
			}

			settings = settings->NextSiblingElement();
			// up vector
			if (settings != NULL) {
				ux = atof(settings->Attribute("x"));
				uy = atof(settings->Attribute("y"));
				uz = atof(settings->Attribute("z"));
			}

			settings = settings->NextSiblingElement();
			// projection
			if (settings != NULL) {
				fov = atof(settings->Attribute("fov"));
				near = atof(settings->Attribute("near"));
				far = atof(settings->Attribute("far"));
			}
		}

		elem = elem->NextSiblingElement();
		// model.3d files
		if (elem != NULL) {
			XMLElement* models = elem->FirstChildElement();
			XMLElement* model = models->FirstChildElement();
			for (; model != NULL; model = model->NextSiblingElement()) {
				string file3d = model->Attribute("file");
				modelReader(path + file3d);
			}
		}
	}
	else cout << "ERROR loading xml file..." << endl;

	return;
}

int main(int argc, char **argv) {
// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Engine - Phase 1");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

// put here the registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	xmlReader(path + argv[1]);
	spherical2Cartesian();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}