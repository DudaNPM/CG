#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

string path = "../ficheiros/";

void build_vertices_plane(int size, int divisions, string file_name) {
    ofstream file(path + file_name);

    int it = 1; // numero de iteracoes
    float inc = (float)size / (float)divisions; // incremento
	float limite = (float)size / (float)2.0f; // limite influenciado pelo size

    // ponto inicial
	float x = -limite;
	float y = 0.0f;
	float z = -limite;

    while (it <= pow(divisions,2)) {
        // 1º triangulo
        file << x << " " << y << " " << z << endl;
        z = z + inc;
        file << x << " " << y << " " << z << endl;
        x = x + inc;
        file << x << " " << y << " " << z << endl;
        // 2º triangulo
        file << x << " " << y << " " << z << endl;
        z = z - inc;
        file << x << " " << y << " " << z << endl;
        x = x - inc;
        file << x << " " << y << " " << z << endl;

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

        file << x << " " << y << " " << z << endl;
        z = z + inc;
        file << x << " " << y << " " << z << endl;
        x = x + inc;
        file << x << " " << y << " " << z << endl;
        file << x << " " << y << " " << z << endl;
        z = z - inc;
        file << x << " " << y << " " << z << endl;
        x = x - inc;
        file << x << " " << y << " " << z << endl;

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

        file << x << " " << y << " " << z << endl;
        x = x + inc;
        file << x << " " << y << " " << z << endl;
        z = z + inc;
        file << x << " " << y << " " << z << endl;
        file << x << " " << y << " " << z << endl;
        x = x - inc;
        file << x << " " << y << " " << z << endl;
        z = z - inc;
        file << x << " " << y << " " << z << endl;

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

    // lateral 1
	x = -aux;
    y = -(float)size / 2.0f;
	z = -aux;

    while (it <= pow(divisions,2)) {

        file << x << " " << y << " " << z << endl;
        y = y + inc;
        file << x << " " << y << " " << z << endl;
        x = x + inc;
        y = y - inc;
        file << x << " " << y << " " << z << endl;
        file << x << " " << y << " " << z << endl;
        x = x - inc;
        y = y + inc;
        file << x << " " << y << " " << z << endl;
        x = x + inc;
        file << x << " " << y << " " << z << endl;

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

    // lateral 2
	x = -aux;
    y = -(float)size / 2.0f;
	z = -aux;

    while (it <= pow(divisions,2)) {

        file << x << " " << y << " " << z << endl;
        z = z + inc;
        file << x << " " << y << " " << z << endl;
        z = z - inc;
        y = y + inc;
        file << x << " " << y << " " << z << endl;
        file << x << " " << y << " " << z << endl;
        z = z + inc;
        y = y - inc;
        file << x << " " << y << " " << z << endl;
        y = y + inc;
        file << x << " " << y << " " << z << endl;

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

    // lateral 3
	x = aux;
    y = -(float)size / 2.0f;
	z = aux;

    while (it <= pow(divisions,2)) {

        file << x << " " << y << " " << z << endl;
        z = z - inc;
        file << x << " " << y << " " << z << endl;
        z = z + inc;
        y = y + inc;
        file << x << " " << y << " " << z << endl;
        file << x << " " << y << " " << z << endl;
        z = z - inc;
        y = y - inc;
        file << x << " " << y << " " << z << endl;
        y = y + inc;
        file << x << " " << y << " " << z << endl;

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

    // lateral 4
	x = aux;
    y = -(float)size / 2.0f;
	z = aux;

    while (it <= pow(divisions,2)) {

        file << x << " " << y << " " << z << endl;
        y = y + inc;
        file << x << " " << y << " " << z << endl;
        x = x - inc;
        y = y - inc;
        file << x << " " << y << " " << z << endl;
        file << x << " " << y << " " << z << endl;
        x = x + inc;
        y = y + inc;
        file << x << " " << y << " " << z << endl;
        x = x - inc;
        file << x << " " << y << " " << z << endl;

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

	for (int j = 0; j < stacks; j++) {
		beta1 = beta * j;		   // angulo camada atual
		beta2 = beta * (j + 1.0f); // angulo camada seguinte

		for (int i = 0; i < slices; i++) {
			alpha1 = alpha * i;			 // angulo fatia atual
			alpha2 = alpha * (i + 1.0f); // angulo fatia seguinte

			// primeiro triangulo de cada camada
            file << radius * sin(beta1) * sin(alpha1) << " " << radius * cos(beta1) << " " << radius * sin(beta1) * cos(alpha1) << endl;
            file << radius * sin(beta2) * sin(alpha1) << " " << radius * cos(beta2) << " " << radius * sin(beta2) * cos(alpha1) << endl;
            file << radius * sin(beta2) * sin(alpha2) << " " << radius * cos(beta2) << " " << radius * sin(beta2) * cos(alpha2) << endl;
			// segundo triangulo de cada camada
            file << radius * sin(beta2) * sin(alpha2) << " " << radius * cos(beta2) << " " << radius * sin(beta2) * cos(alpha2) << endl;
            file << radius * sin(beta1) * sin(alpha2) << " " << radius * cos(beta1) << " " << radius * sin(beta1) * cos(alpha2) << endl;
            file << radius * sin(beta1) * sin(alpha1) << " " << radius * cos(beta1) << " " << radius * sin(beta1) * cos(alpha1) << endl;
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

        file <<                    0 << " " << 0 << " " <<                    0 << endl;
        file << radius * sin(alpha2) << " " << 0 << " " << radius * cos(alpha2) << endl;
        file << radius * sin(alpha1) << " " << 0 << " " << radius * cos(alpha1) << endl;
	}


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
            file << fatia1 * sin(alpha1) << " " << camada1 << " " << fatia1 * cos(alpha1) << endl;
            file << fatia1 * sin(alpha2) << " " << camada1 << " " << fatia1 * cos(alpha2) << endl;
            file << fatia2 * sin(alpha2) << " " << camada2 << " " << fatia2 * cos(alpha2) << endl;
			// segundo triangulo de cada camada
            file << fatia1 * sin(alpha1) << " " << camada1 << " " << fatia1 * cos(alpha1) << endl;
            file << fatia2 * sin(alpha2) << " " << camada2 << " " << fatia2 * cos(alpha2) << endl;
            file << fatia2 * sin(alpha1) << " " << camada2 << " " << fatia2 * cos(alpha1) << endl;
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
        file <<      0 << " " << height << " " <<      0 << endl;
        file << last_x << " " << height << " " << last_z << endl;
        file <<      x << " " << height << " " <<      z << endl;
		// corpo (cima -> baixo)
        file << last_x << " " << height << " " << last_z << endl;
        file << last_x << " " <<      0 << " " << last_z << endl;
        file <<      x << " " << height << " " <<      z << endl;
		// corpo (baixo -> cima)
        file <<      x << " " <<      0 << " " <<      z << endl;
        file <<      x << " " << height << " " <<      z << endl;
        file << last_x << " " <<      0 << " " << last_z << endl;
		// base
        file <<      0 << " " << 0 << " " <<      0 << endl;
        file <<      x << " " << 0 << " " <<      z << endl;
        file << last_x << " " << 0 << " " << last_z << endl;
		
		last_x = x;
		last_z = z;
	}
}


void multMatrixVector(float* m, float* v, float* res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }
}


void bezierPatches(float u, float v, int* indices, float** cp, float* coord) {

    float U[4] = {powf(u,3), powf(u,2), u, 1.0};
    float V[4] = {powf(v,3), powf(v,2), v, 1.0};

    float M[4][4] = {{-1.0f,  3.0f, -3.0f,  1.0f},
                     { 3.0f, -6.0f,  3.0f,  0.0f},
                     {-3.0f,  3.0f,  0.0f,  0.0f},
                     { 1.0f,  0.0f,  0.0f,  0.0f}};
    
    float px[4][4], py[4][4], pz[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int ind = indices[i * 4 + j];
            px[i][j] = cp[ind][0];
            py[i][j] = cp[ind][1];
            pz[i][j] = cp[ind][2];
        }
    }

    // B(u,v) = U * M * P * MT * V
    // M = MT

    float  UM[4], MV[4], UMV[4], x, y, z, resx[4], resy[4], resz[4];
    float resMx[4], resMy[4], resMz[4];
    multMatrixVector((float*)M, U, UM);
    multMatrixVector((float*)px, UM, resx);
    multMatrixVector((float*)py, UM, resy);
    multMatrixVector((float*)pz, UM, resz);
    multMatrixVector((float*)M, resx, resMx);
    multMatrixVector((float*)M, resy, resMy);
    multMatrixVector((float*)M, resz, resMz);
    x = resMx[0] * V[0] + resMx[1] * V[1] + resMx[2] * V[2] + resMx[3] * V[3];
    y = resMy[0] * V[0] + resMy[1] * V[1] + resMy[2] * V[2] + resMy[3] * V[3];
    z = resMz[0] * V[0] + resMz[1] * V[1] + resMz[2] * V[2] + resMz[3] * V[3];

    coord[0] = x;
    coord[1] = y;
    coord[2] = z;
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

            for (int i = 0; i < patches; i++) {
                for (float u = 0; u < 1; u += inc) {
                    for (float v = 0; v < 1; v += inc) {

                        bezierPatches(      u,       v, indices[i], cp, p1);
                        bezierPatches(      u, v + inc, indices[i], cp, p2);
                        bezierPatches(u + inc,       v, indices[i], cp, p3);
                        bezierPatches(u + inc, v + inc, indices[i], cp, p4);

                        out << p4[0] << " " << p4[1] << " " << p4[2] << endl;
                        out << p3[0] << " " << p3[1] << " " << p3[2] << endl;
                        out << p2[0] << " " << p2[1] << " " << p2[2] << endl;

                        out << p3[0] << " " << p3[1] << " " << p3[2] << endl;
                        out << p1[0] << " " << p1[1] << " " << p1[2] << endl;
                        out << p2[0] << " " << p2[1] << " " << p2[2] << endl;
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
