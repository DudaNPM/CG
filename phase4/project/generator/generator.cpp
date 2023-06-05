#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

string path = "../ficheiros/";


float find_texture_plane(float value, float size) {
    // (value – min) / (max – min)
    float min = -size / 2.0f;
    float max = -min;
    float normalized = (value - min) / (max - min);
    return normalized;
}


void build_vertices_plane(int size, int divisions, string file_name) {
    ofstream file(path + file_name);

    int it = 1; // numero de iteracoes
    float inc = (float)size / (float)divisions; // incremento
	float limite = (float)size / (float)2.0f; // limite influenciado pelo size

    // ponto inicial
	float x = -limite;
	float y = 0.0f;
	float z = -limite;

    float u = x;
    float v = z;

    while (it <= pow(divisions,2)) {
        // 1º triangulo
        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << 0 << " " << 0 << endl;
        z = z + inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << 0 << " " << 1 << endl;
        x = x + inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << 1 << " " << 1 << endl;
        // 2º triangulo
        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << 1 << " " << 1 << endl;
        z = z - inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << 1 << " " << 0 << endl;
        x = x - inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << 0 << " " << 0 << endl;

        // preparacao para a proxima iteracao
        x = x + inc;
        it++;

        // uma linha esta completa, passa para a proxima coluna
        // if (x == limite) ....
        if (trunc(1000. * x) == trunc(1000. * limite)) {
			z = z + inc;
			x = -limite;
		}
    }
}

void build_vertices_box(int size, int divisions, string file_name) {
    ofstream file(path + file_name);

    float inc = (float)size / (float)divisions; // incremento
	float aux = (float)size / (float)2.0f; // limite

    int it = 1; // numero de iteracoes

    // topo
    // ponto inicial
	float x = -aux;
    float y = (float)size / 2.0f;
	float z = -aux;

    while (it <= pow(divisions,2)) {

        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;
        z = z + inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;
        x = x + inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;
        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;
        z = z - inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;
        x = x - inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;

        // preparacao para a proxima iteracao
        x = x + inc;
        it++;

        // uma linha esta completa, passa para a proxima coluna
        if (trunc(1000. * x) == trunc(1000. * aux)) {
			z = z + inc;
			x = -aux;
		}
    }


    it = 1; // numero de iteracoes

    // base
	x = -aux;
    y = -(float)size / 2.0f;
	z = -aux;

    while (it <= pow(divisions,2)) {

        file << x << " " << y << " " << z << " " << 0 << " " << -1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;
        x = x + inc;
        file << x << " " << y << " " << z << " " << 0 << " " << -1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;
        z = z + inc;
        file << x << " " << y << " " << z << " " << 0 << " " << -1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;
        file << x << " " << y << " " << z << " " << 0 << " " << -1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;
        x = x - inc;
        file << x << " " << y << " " << z << " " << 0 << " " << -1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;
        z = z - inc;
        file << x << " " << y << " " << z << " " << 0 << " " << -1 << " " << 0 << " " << find_texture_plane(x, size) << " " << find_texture_plane(z, size) << endl;

        // preparacao para a proxima iteracao
        x = x + inc;
        it++;

        // uma linha esta completa, passa para a proxima coluna
        if (trunc(1000. * x) == trunc(1000. * aux)) {
			z = z + inc;
			x = -aux;
		}
    }


    it = 1; // numero de iteracoes

    // lateral 1 (tras)
	x = -aux;
    y = -(float)size / 2.0f;
	z = -aux;

    while (it <= pow(divisions,2)) {

        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << -1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;
        y = y + inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << -1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;
        x = x + inc;
        y = y - inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << -1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;
        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << -1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;
        x = x - inc;
        y = y + inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << -1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;
        x = x + inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << -1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;

        // preparacao para a proxima iteracao
        y = y - inc;
        it++;

        // uma linha esta completa, passa para a proxima coluna
        if (trunc(1000. * x) == trunc(1000. * aux)) {
			y = y + inc;
			x = -aux;
		}
    }


    it = 1; // numero de iteracoes

    // lateral 2 (esquerda)
	x = -aux;
    y = -(float)size / 2.0f;
	z = -aux;

    while (it <= pow(divisions,2)) {

        file << x << " " << y << " " << z << " " << -1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;
        z = z + inc;
        file << x << " " << y << " " << z << " " << -1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;
        z = z - inc;
        y = y + inc;
        file << x << " " << y << " " << z << " " << -1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;
        file << x << " " << y << " " << z << " " << -1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;
        z = z + inc;
        y = y - inc;
        file << x << " " << y << " " << z << " " << -1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;
        y = y + inc;
        file << x << " " << y << " " << z << " " << -1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;

        // preparacao para a proxima iteracao
        y = y - inc;
        it++;

        // uma linha esta completa, passa para a proxima coluna
        if (trunc(1000. * z) == trunc(1000. * aux)) {
			y = y + inc;
			z = -aux;
		}
    }


    it = 1; // numero de iteracoes

    // lateral 3 (direita)
	x = aux;
    y = -(float)size / 2.0f;
	z = aux;

    while (it <= pow(divisions,2)) {

        file << x << " " << y << " " << z << " " << 1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;
        z = z - inc;
        file << x << " " << y << " " << z << " " << 1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;
        z = z + inc;
        y = y + inc;
        file << x << " " << y << " " << z << " " << 1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;
        file << x << " " << y << " " << z << " " << 1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;
        z = z - inc;
        y = y - inc;
        file << x << " " << y << " " << z << " " << 1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;
        y = y + inc;
        file << x << " " << y << " " << z << " " << 1 << " " << 0 << " " << 0 << " " << find_texture_plane(z, size) << " " << find_texture_plane(y, size) << endl;

        // preparacao para a proxima iteracao
        y = y - inc;
        it++;

        // uma linha esta completa, passa para a proxima coluna
        if (trunc(1000. * z) == trunc(1000. * -aux)) {
			y = y + inc;
			z = aux;
		}
    }


    it = 1; // numero de iteracoes

    // lateral 4 (frente)
	x = aux;
    y = -(float)size / 2.0f;
	z = aux;

    while (it <= pow(divisions,2)) {

        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << 1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;
        y = y + inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << 1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;
        x = x - inc;
        y = y - inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << 1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;
        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << 1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;
        x = x + inc;
        y = y + inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << 1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;
        x = x - inc;
        file << x << " " << y << " " << z << " " << 0 << " " << 0 << " " << 1 << " " << find_texture_plane(x, size) << " " << find_texture_plane(y, size) << endl;

        // preparacao para a proxima iteracao
        y = y - inc;
        it++;

        // uma linha esta completa, passa para a proxima coluna
        if (trunc(1000. * x) == trunc(1000. * -aux)) {
			y = y + inc;
			x = aux;
		}
    }
}



void build_vertices_sphere(int radius, int slices, int stacks, string file_name) {
    ofstream file(path + file_name);

    float alpha = 2 * M_PI / (float)slices; // angulo entre fatias
	float beta = M_PI / (float)stacks;      // angulo entre camadas
	float alpha1, alpha2, beta1, beta2;
    float ladoInc = 1.0 / (float)slices;
    float cimaInc = 1.0 / (float)stacks;

	for (float j = 0; j < stacks; j++) {
		beta1 = beta * j;		   // angulo camada atual
		beta2 = beta * (j + 1.0f); // angulo camada seguinte

		for (float i = 0; i < slices; i++) {
			alpha1 = alpha * i;			 // angulo fatia atual
			alpha2 = alpha * (i + 1.0f); // angulo fatia seguinte

            float x1 = (float)radius * sinf(beta1) * sinf(alpha1);
            float y1 = (float)radius * cosf(beta1);
            float z1 = (float)radius * sinf(beta1) * cosf(alpha1);
            float x2 = (float)radius * sinf(beta2) * sinf(alpha1);
            float y2 = (float)radius * cosf(beta2);
            float z2 = (float)radius * sinf(beta2) * cosf(alpha1);
            float x3 = (float)radius * sinf(beta2) * sinf(alpha2);
            float z3 = (float)radius * sinf(beta2) * cosf(alpha2);
            float x4 = (float)radius * sinf(beta1) * sinf(alpha2);
            float z4 = (float)radius * sinf(beta1) * cosf(alpha2);

            float nx1 = x1 / (float)radius; float ny1 = y1 / (float)radius; float nz1 = z1 / (float)radius;
            float nx2 = x2 / (float)radius; float ny2 = y2 / (float)radius; float nz2 = z2 / (float)radius;
            float nx3 = x3 / (float)radius;                                 float nz3 = z3 / (float)radius;
            float nx4 = x4 / (float)radius;                                 float nz4 = z4 / (float)radius;

			// primeiro triangulo de cada camada
            file << x1 << " " << y1 << " " << z1 << " " << nx1 << " " << ny1 << " " << nz1 << " " << (      i / (float)slices) << " " << ((stacks - j    ) / (float)stacks) << endl;
            file << x2 << " " << y2 << " " << z2 << " " << nx2 << " " << ny2 << " " << nz2 << " " << (      i / (float)slices) << " " << ((stacks - j - 1) / (float)stacks) << endl;
            file << x3 << " " << y2 << " " << z3 << " " << nx3 << " " << ny2 << " " << nz3 << " " << ((i + 1) / (float)slices) << " " << ((stacks - j - 1) / (float)stacks) << endl;
			// segundo triangulo de cada camada
            file << x3 << " " << y2 << " " << z3 << " " << nx3 << " " << ny2 << " " << nz3 << " " << ((i + 1) / (float)slices) << " " << ((stacks - j - 1) / (float)stacks) << endl;
            file << x4 << " " << y1 << " " << z4 << " " << nx4 << " " << ny1 << " " << nz4 << " " << ((i + 1) / (float)slices) << " " << ((stacks - j    ) / (float)stacks) << endl;
            file << x1 << " " << y1 << " " << z1 << " " << nx1 << " " << ny1 << " " << nz1 << " " << (      i / (float)slices) << " " << ((stacks - j    ) / (float)stacks) << endl;
		}
	}
}


void build_vertices_cone(int radius, int height, int slices, int stacks, string file_name) {
    ofstream file(path + file_name);
    
    float alpha = 2 * M_PI / slices;               // angulo de cada fatia
	float camada = (float)height / (float)stacks;  // altura da primeira camada
	float alpha1, fatia1, camada1;
	float alpha2, fatia2, camada2;


	// base
	for (int n = 0; n < slices; n++) {
		alpha1 = alpha * n;      // angulo fatia atual
		alpha2 = alpha1 + alpha; // angulo fatia seguinte

        file <<                    0 << " " << 0 << " " <<                    0 << " " << 0 << " " << -1 << " " << 0 << " " << 0 << " " << 0 << endl;
        file << radius * sin(alpha2) << " " << 0 << " " << radius * cos(alpha2) << " " << 0 << " " << -1 << " " << 0 << " " << 0 << " " << 0 << endl;
        file << radius * sin(alpha1) << " " << 0 << " " << radius * cos(alpha1) << " " << 0 << " " << -1 << " " << 0 << " " << 0 << " " << 0 << endl;
	}

    float aux = M_PI - M_PI / 2 - atan2(height, radius);
	// camadas
	for (int i = 0; i < stacks; i++) {
		camada1 = camada * i;       // altura camada atual
		camada2 = camada * (i + 1); // altura camada seguinte

		fatia1 = (float)radius - (((float)radius / (float)stacks) * i);        // raio da fatia atual
		fatia2 = (float)radius - (((float)radius / (float)stacks) * (i + 1));  // raio da fatia seguinte

		// lados
		for (int j = 0; j < slices; j++) {
			alpha1 = alpha * j;		  // angulo fatia atual
			alpha2 = alpha * (j + 1); // angulo fatia seguinte

			// primeiro triangulo de cada camada
            file << fatia1 * sin(alpha1) << " " << camada1 << " " << fatia1 * cos(alpha1) << " " << sin(alpha1) << " " << aux << " " << cos(alpha1) << " " << camada1 / (float)height << " " << sin(alpha1) << endl;
            file << fatia1 * sin(alpha2) << " " << camada1 << " " << fatia1 * cos(alpha2) << " " << sin(alpha2) << " " << aux << " " << cos(alpha2) << " " << camada1 / (float)height << " " << sin(alpha2) << endl;
            file << fatia2 * sin(alpha2) << " " << camada2 << " " << fatia2 * cos(alpha2) << " " << sin(alpha2) << " " << aux << " " << cos(alpha2) << " " << camada2 / (float)height << " " << sin(alpha2) << endl;
			// segundo triangulo de cada camada
            file << fatia1 * sin(alpha1) << " " << camada1 << " " << fatia1 * cos(alpha1) << " " << sin(alpha1) << " " << aux << " " << cos(alpha1) << " " << camada1 / (float)height << " " << sin(alpha1) << endl;
            file << fatia2 * sin(alpha2) << " " << camada2 << " " << fatia2 * cos(alpha2) << " " << sin(alpha2) << " " << aux << " " << cos(alpha2) << " " << camada2 / (float)height << " " << sin(alpha2) << endl;
            file << fatia2 * sin(alpha1) << " " << camada2 << " " << fatia2 * cos(alpha1) << " " << sin(alpha1) << " " << aux << " " << cos(alpha1) << " " << camada2 / (float)height << " " << sin(alpha1) << endl;
		}
	}
}


void build_vertices_cylinder(int radius, int height, int slices, string file_name) {
    ofstream file(path + file_name);

    float alpha = 2 * M_PI / (float)slices;
	float x, z;
	float last_x = radius * sin(0);
	float last_z = radius * cos(0);
	
	for (int i = 1; i <= slices; i++) {
        
		x = radius * sin(i*alpha);
		z = radius * cos(i*alpha);

		// topo
        file <<      0 << " " << height << " " <<      0 << " " << 0 << " " << 1 << " " << 0 << endl;
        file << last_x << " " << height << " " << last_z << " " << 0 << " " << 1 << " " << 0 << endl;
        file <<      x << " " << height << " " <<      z << " " << 0 << " " << 1 << " " << 0 << endl;
		// corpo (cima -> baixo)
        file << last_x << " " << height << " " << last_z << " " << last_x / radius << " " << 0 << " " << last_z / radius << endl;
        file << last_x << " " <<      0 << " " << last_z << " " << last_x / radius << " " << 0 << " " << last_z / radius << endl;
        file <<      x << " " << height << " " <<      z << " " <<      x / radius << " " << 0 << " " <<      z / radius << endl;
		// corpo (baixo -> cima)
        file <<      x << " " <<      0 << " " <<      z << " " <<      x / radius << " " << 0 << " " <<      z / radius << endl;
        file <<      x << " " << height << " " <<      z << " " <<      x / radius << " " << 0 << " " <<      z / radius << endl;
        file << last_x << " " <<      0 << " " << last_z << " " << last_x / radius << " " << 0 << " " << last_z / radius << endl;
		// base
        file <<      0 << " " << 0 << " " <<      0 << " " << 0 << " " << -1 << " " << 0 << endl;
        file <<      x << " " << 0 << " " <<      z << " " << 0 << " " << -1 << " " << 0 << endl;
        file << last_x << " " << 0 << " " << last_z << " " << 0 << " " << -1 << " " << 0 << endl;
		
		last_x = x;
		last_z = z;
	}
}


void cross(float* a, float* b, float* res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}


void multMatrix(float* m1, float* m2, float* res, int a, int b, int c) {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            res[4 * i + j] = 0;
            for (int k = 0; k < c; k++) {
                if (a == 1 && b == 1) { res[4 * i + j] += m1[4 * i + k] * m2[4 * j + k]; }
                else { res[4 * i + j] += m1[4 * i + k] * m2[4 * k + j]; }
            }
        }
    }
}


void bezierPatches(float u, float v, int* indices, float** cp, float* coord, float* normal) {

    float px[4][4], py[4][4], pz[4][4];

    // coordenadas
    float res[1][4], resX[1][4], resY[1][4], resZ[1][4];
    float resTX[1][4], resTY[1][4], resTZ[1][4];
    float x[1], y[1], z[1];

    // derivada U
    float resU[1][4], resUX[1][4], resUY[1][4], resUZ[1][4];
    float resUTX[1][4], resUTY[1][4], resUTZ[1][4];
    float Ux[1], Uy[1], Uz[1];

    // derivada V
    float resV[1][4], resVX[1][4], resVY[1][4], resVZ[1][4];
    float resVTX[1][4], resVTY[1][4], resVTZ[1][4];
    float Vx[1], Vy[1], Vz[1];

    float M[4][4] = {{-1.0f,  3.0f, -3.0f,  1.0f},
                     { 3.0f, -6.0f,  3.0f,  0.0f},
                     {-3.0f,  3.0f,  0.0f,  0.0f},
                     { 1.0f,  0.0f,  0.0f,  0.0f}};

    float U[1][4] = {{powf(u,3), powf(u,2), u, 1}};
    float V[4][1] = {{powf(v,3)}, {powf(v,2)}, {v}, {1}};
    float devU[1][4] = {{3*powf(u,2), 2*powf(u,1), 1, 0}};
    float devV[4][1] = {{3*powf(v,2)}, {2*powf(v,1)}, {1}, {0}};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int ind = indices[i * 4 + j];
            px[i][j] = cp[ind][0];
            py[i][j] = cp[ind][1];
            pz[i][j] = cp[ind][2];
        }
    }


    // Formula = U * M * P * MT * V
    // coordenadas
    multMatrix(*U, *M, *res, 1, 4, 4);
    multMatrix(*res, *px, *resX, 1, 4, 4);
    multMatrix(*res, *py, *resY, 1, 4, 4);
    multMatrix(*res, *pz, *resZ, 1, 4, 4);
    multMatrix(*resX, *M, *resTX, 1, 4, 4);
    multMatrix(*resY, *M, *resTY, 1, 4, 4);
    multMatrix(*resZ, *M, *resTZ, 1, 4, 4);
    multMatrix(*resTX, *V, x, 1, 1, 4);
    multMatrix(*resTY, *V, y, 1, 1, 4);
    multMatrix(*resTZ, *V, z, 1, 1, 4);
    coord[0] = x[0]; coord[1] = y[0]; coord[2] = z[0];

    // Formula = devU * M * P * MT * VT
    // derivada U
    multMatrix(*devU, *M, *resU, 1, 4, 4);
    multMatrix(*resU, *px, *resUX, 1, 4, 4);
    multMatrix(*resU, *py, *resUY, 1, 4, 4);
    multMatrix(*resU, *pz, *resUZ, 1, 4, 4);
    multMatrix(*resUX, *M, *resUTX, 1, 4, 4);
    multMatrix(*resUY, *M, *resUTY, 1, 4, 4);
    multMatrix(*resUZ, *M, *resUTZ, 1, 4, 4);
    multMatrix(*resUTX, *V, Ux, 1, 1, 4);
    multMatrix(*resUTY, *V, Uy, 1, 1, 4);
    multMatrix(*resUTZ, *V, Uz, 1, 1, 4);
    float vetorU[3] = { Ux[0], Uy[0], Uz[0] };

    // Formula = U * M * P * MT * devV
    // derivada V
    multMatrix(*U, *M, *resV, 1, 4, 4);
    multMatrix(*resV, *px, *resVX, 1, 4, 4);
    multMatrix(*resV, *py, *resVY, 1, 4, 4);
    multMatrix(*resV, *pz, *resVZ, 1, 4, 4);
    multMatrix(*resVX, *M, *resVTX, 1, 4, 4);
    multMatrix(*resVY, *M, *resVTY, 1, 4, 4);
    multMatrix(*resVZ, *M, *resVTZ, 1, 4, 4);
    multMatrix(*resVTX, *devV, Vx, 1, 1, 4);
    multMatrix(*resVTY, *devV, Vy, 1, 1, 4);
    multMatrix(*resVTZ, *devV, Vz, 1, 1, 4);
    float vetorV[3] = { Vx[0], Vy[0], Vz[0] };

    // cross product das tangentes
    cross(vetorV, vetorU, normal);
}


void build_bezier(string input, int tesselation, string output) {
    ifstream in(path + input);
    ofstream out(path + output);
    
    int patches = 0;    // numero de patches
    int** indices;      // indices dos control points
    int numcp = 0;      // numero de control points
    float** cp;         // control points
    
    string read;

    // leitura do ficheiro .patch
    if (in.is_open()) {

        // leitura do numero de patches
        getline(in, read);
        patches = stoi(read);

        // leitura dos indices de cada patch
        // 16 indices por linha
        indices = new int* [patches];
        for (int i = 0; i < patches; i++) {
            indices[i] = new int[16];
            getline(in, read);
            char* linha = strdup(read.c_str());
            char* token = strtok(linha, ", ");
            for (int j = 0; token != NULL; j++) {
                indices[i][j] = stoi(token);
                token = strtok(NULL, ", ");
            }
        }
        
        // leitura do numero de control points
        getline(in, read);
        numcp = stoi(read);

        // leitura dos valores dos control points
        // cada control point, ou seja, cada linha contem 3 coords
        cp = new float* [numcp];
        for (int i = 0; i < numcp; i++) {
            cp[i] = new float[3];
            getline(in, read);
            char* linha = strdup(read.c_str());
            char* token = strtok(linha, ", ");
            for (int j = 0; token != NULL; j++) {
                cp[i][j] = stof(token);
                token = strtok(NULL, ", ");
            }
        }
        

        // escrita para o ficheiro .3d
        if (out.is_open()) {

            float inc = 1.0 / tesselation;
            float p1[3], p2[3], p3[3], p4[3];
            float normal1[3], normal2[3], normal3[3], normal4[3];

            for (int i = 0; i < patches; i++) {
                for (float u = 0; u < 1; u += inc) {
                    for (float v = 0; v < 1; v += inc) {
                        float u1 = u + inc;
                        float v1 = v + inc;
                        
                        bezierPatches( u,  v, indices[i], cp, p1, normal1);
                        bezierPatches( u, v1, indices[i], cp, p2, normal2);
                        bezierPatches(u1,  v, indices[i], cp, p3, normal3);
                        bezierPatches(u1, v1, indices[i], cp, p4, normal4);

                        out << p4[0] << " " << p4[1] << " " << p4[2] << " " << normal4[0] << " " << normal4[1] << " " << normal4[2] << " " << u1 << " " << v1 << endl;
                        out << p3[0] << " " << p3[1] << " " << p3[2] << " " << normal3[0] << " " << normal3[1] << " " << normal3[2] << " " << u1 << " " <<  v << endl;
                        out << p2[0] << " " << p2[1] << " " << p2[2] << " " << normal2[0] << " " << normal2[1] << " " << normal2[2] << " " <<  u << " " << v1 << endl;

                        out << p3[0] << " " << p3[1] << " " << p3[2] << " " << normal3[0] << " " << normal3[1] << " " << normal3[2] << " " << u1 << " " <<  v << endl;
                        out << p1[0] << " " << p1[1] << " " << p1[2] << " " << normal1[0] << " " << normal1[1] << " " << normal1[2] << " " <<  u << " " <<  v << endl;
                        out << p2[0] << " " << p2[1] << " " << p2[2] << " " << normal2[0] << " " << normal2[1] << " " << normal2[2] << " " <<  u << " " << v1 << endl;
                    }
                }
            }
        }
        else cout << "ERROR writing file!" << endl;
    }
    else cout << "ERROR reading file!" << endl;
    in.close();
    out.close();
}


int main(int argc, char** argv) {

    // figura em questao
    string figure = argv[1];
    // plano & cubo
    int size, divisions;
    // esfera
    int sphere_radius, sphere_slices, sphere_stacks;
    // cone
    int cone_radius, cone_height, cone_slices, cone_stacks;
    // cilindro
    int cylinder_radius, cylinder_height, cylinder_slices;
    // bezier
    string patch;
    int tesselation;
    // ficheiro
    string file_name;
    // leitura dos argumentos
    bool args = false;

    if (figure == "plane" || figure == "box") {
        size = stoi(argv[2]);
        divisions = stoi(argv[3]);
        file_name = argv[4];
        args = true;

        if (figure == "plane")
            build_vertices_plane(size,divisions,file_name);
        if (figure == "box")
            build_vertices_box(size,divisions,file_name);
    }
	

    if (figure == "sphere") {
        sphere_radius = stoi(argv[2]);
        sphere_slices = stoi(argv[3]);
        sphere_stacks = stoi(argv[4]);
        file_name = argv[5];
        args = true;

        build_vertices_sphere(sphere_radius,sphere_slices,sphere_stacks,file_name);
    }


    if (figure == "cone") {
        cone_radius = stoi(argv[2]);
        cone_height = stoi(argv[3]);
        cone_slices = stoi(argv[4]);
        cone_stacks = stoi(argv[5]);
        file_name = argv[6];
        args = true;

        build_vertices_cone(cone_radius,cone_height,cone_slices,cone_stacks,file_name);
    }

    
    if (figure == "cylinder") {
        cylinder_radius = stoi(argv[2]);
        cylinder_height = stoi(argv[3]);
        cylinder_slices = stoi(argv[4]);
        file_name = argv[5];
        args = true;

        build_vertices_cylinder(cylinder_radius,cylinder_height,cylinder_slices,file_name);
    }

    if (figure == "bezier") {
        patch = argv[2];
        tesselation = stoi(argv[3]);
        file_name = argv[4];
        args = true;

        build_bezier(patch, tesselation, file_name);
    }

    // caso não se leia nehuma das figuras anteriores
    if (!args) cout << "Erro na leitura dos parâmetros..." << endl;
	return 0;
}
