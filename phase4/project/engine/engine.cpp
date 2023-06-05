#include "engine.h"

// controladores extras:
bool eixoCentral = true;	// eixo central
bool eixos = false;			// eixos secundarios
bool polymode = true;		// modo de apresentacao
bool vbo = true;			// vbo
bool curves = true;			// orbitas
bool stop = false;			// pause

float calpha = 0.0f, cbeta = 0.0f;	// angulos da camara
float cdist;						// distancia da camara
float cx, cy, cz;					// camera position
float lx, ly, lz;					// lookAt point
float ux, uy, uz;					// up vector
float fov, near, far;				// projection
int startX, startY, tracking = 0;	// mouse

// FPS
int timebase;
float frames;

string path = "../ficheiros/";
vector<Group>* groups;
Camera* camera;
vector<Light*> lights;


void fps() {
	char title[50];
	frames++;
	double time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		double fps = frames * 1000.0 / (time - timebase);
		timebase = time;
		frames = 0;
		sprintf_s(title, "Engine - Phase 4 | %lf FPS", fps);
		glutSetWindowTitle(title);
	}
}


void spherical2Cartesian() {
	cx = cdist * cos(cbeta) * sin(calpha);
	cy = cdist * sin(cbeta);
	cz = cdist * cos(cbeta) * cos(calpha);
}


void drawObject() {
	for (Group group : *groups)
		group.draw(vbo, eixos, curves, stop);
}


void loadCamera(Camera* c) {
	cx = c->getXPos(); cy = c->getYPos(); cz = c->getZPos();
	lx = c->getXLa(); ly = c->getYLa(); lz = c->getZLa();
	ux = c->getXUp(); uy = c->getYUp(); uz = c->getZUp();
	fov = c->getFov(); near = c->getNear(); far = c->getFar();

	cbeta = atan(cy / (sqrt(pow(cx, 2) + pow(cz, 2))));
	cdist = cy / sin(cbeta);
	calpha = acos(cz / (cdist * cos(cbeta)));
}


void buildCentralAxis() {
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100000.0f, 0.0f, 0.0f);
	glVertex3f(100000.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100000.0f, 0.0f);
	glVertex3f(0.0f, 100000.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100000.0f);
	glVertex3f(0.0f, 0.0f, 100000.0f);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
}


void run(string f) {
	groups = new vector<Group>();
	camera = new Camera();
	xmlReader(f, camera, &lights, groups);
	loadCamera(camera);
}


void printInfo() {
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n\n", glGetString(GL_VERSION));

	printf("Use mouse left button to move arround\n");
	printf("Use mouse right button to zoom in/out\n");
	printf("Controls:\n");
	printf("'z' - Show/Hide central axis.\n");
	printf("'x' - Show/Hide secundary axis.\n");
	printf("'c' - Change polygon mode.\n");
	printf("'v' - Enable/Disable VBO mode.\n");
	printf("'p' - Pause/Unpause the solar system.\n");
	printf("'b' - Show/Hide orbits.\n");
}


void printState() {
	printf("\nCurrent state:\n");
	if (eixoCentral) printf("	-Showing central axis.\n");
	else printf("	-Hiding central axis.\n");
	if (eixos) printf("	-Showing secundary axis.\n");
	else printf("	-Hiding secundary axis.\n");
	if (polymode) printf("	-Polygon mode set to GL_FILL.\n");
	else printf("	-Polygon mode set to GL_LINE.\n");
	if (vbo) printf("	-Using VBO mode.\n");
	else printf("	-Using immediate mode.\n");
	if (stop) printf("	-Solar System paused.\n");
	else printf("	-Solar System runnning.\n");
	if (curves) printf("	-Showing orbits.\n");
	else printf("	-Hiding orbits.\n");
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


void renderScene(void) {
	// clear buffers
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// define light position
	for (Light* l : lights)
		l->apply();

	// set the camera
	glLoadIdentity();
	gluLookAt(cx, cy, cz, lx, ly, lz, ux, uy, uz);

	// draw instructions
	if (eixoCentral) buildCentralAxis();

	if (polymode) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	drawObject();

	fps();

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
	switch (c) {
	case 'z':
		eixoCentral = !eixoCentral;
		printState();
		break;
	case 'x':
		eixos = !eixos;
		printState();
		break;
	case 'c':
		polymode = !polymode;
		printState();
		break;
	case 'v':
		vbo = !vbo;
		printState();
		break;
	case 'b':
		curves = !curves;
		printState();
		break;
	case 'p':
		stop = !stop;
		printState();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {
	// ....
	// spherical2Cartesian();
	// glutPostRedisplay();
}


void processMouseButtons(int button, int state, int xx, int yy) {

	if (state == GLUT_DOWN) {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {

		if (tracking == 1) {
			calpha += (xx - startX);
			cbeta += (yy - startY);
		}
		else if (tracking == 2) {

			cdist -= yy - startY;
			if (cdist < 1)
				cdist = 1.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {

		alphaAux = calpha + deltaX;
		betaAux = cbeta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = cdist;
	}
	else if (tracking == 2) {

		alphaAux = calpha;
		betaAux = cbeta;
		rAux = cdist - deltaY;
		if (rAux < 1)
			rAux = 1;
	}
	cx = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	cz = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	cy = rAux * sin(betaAux * 3.14 / 180.0);
}


int main(int argc, char** argv) {
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Engine - Phase 4");

	// required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

#ifndef __APPLE__
	glewInit();
#endif

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// init
	spherical2Cartesian();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_LIGHTING); // turn lighting on
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_RESCALE_NORMAL);
	float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	run(path + argv[1]);
	printInfo();
	printState();

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}