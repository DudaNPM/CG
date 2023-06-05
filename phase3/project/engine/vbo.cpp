#include "vbo.h"

VBO::VBO(vector<Ponto> pontos) {
	this->vertices = 1;
	this->verticeCount = pontos.size() * 3;
	this->prepareData(pontos);
}


void VBO::prepareData(vector<Ponto> pontos) {
	vector<float> coords;

	for (Ponto p : pontos) {
		coords.push_back(p.x);
		coords.push_back(p.y);
		coords.push_back(p.z);
	}

	// criar o VBO
	glGenBuffers(1, &this->vertices);

	// copiar o vector para a memória gráfica
	glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
	glBufferData(
		GL_ARRAY_BUFFER,					// tipo do buffer, só é relevante na altura do desenho
		sizeof(float) * this->verticeCount, // tamanho do vector em bytes
		coords.data(),					    // os dados do array associado ao vector
		GL_STATIC_DRAW);					// indicativo da utilização (estático e para desempenho)
}


void VBO::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, this->verticeCount);
}