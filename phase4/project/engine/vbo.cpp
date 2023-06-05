#include "vbo.h"
#include <iostream>
using namespace std;

VBO::VBO(vector<Ponto> pontos, bool texture) {
	this->verticeCount = pontos.size() * 3;
	this->texture = texture;
	this->prepareData(pontos);
}


void VBO::prepareData(vector<Ponto> pontos) {
	vector<float> coords;
	vector<float> normais;
	vector<float> texturas;

	for (Ponto p : pontos) {
		coords.push_back(p.x);
		coords.push_back(p.y);
		coords.push_back(p.z);
		normais.push_back(p.nx);
		normais.push_back(p.ny);
		normais.push_back(p.nz);
		texturas.push_back(p.ti);
		texturas.push_back(p.tj);
	}

	// criar o VBO
	glGenBuffers(3, this->buffers);

	// copiar o vector para a memória gráfica
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
	glBufferData(
		GL_ARRAY_BUFFER,					// tipo do buffer, só é relevante na altura do desenho
		sizeof(float) * coords.size(),		// tamanho do vector em bytes
		coords.data(),					    // os dados do array associado ao vector
		GL_STATIC_DRAW);					// indicativo da utilização (estático e para desempenho)

	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[1]);
	glBufferData(
		GL_ARRAY_BUFFER,					// tipo do buffer, só é relevante na altura do desenho
		sizeof(float) * normais.size(),	    // tamanho do vector em bytes
		normais.data(),					    // os dados do array associado ao vector
		GL_STATIC_DRAW);					// indicativo da utilização (estático e para desempenho)

	if (this->texture) {
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers[2]);
		glBufferData(
			GL_ARRAY_BUFFER,					// tipo do buffer, só é relevante na altura do desenho
			sizeof(float) * texturas.size(),    // tamanho do vector em bytes
			texturas.data(),					// os dados do array associado ao vector
			GL_STATIC_DRAW);					// indicativo da utilização (estático e para desempenho)
	}
}


void VBO::draw(int textid) {
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[1]);
	glNormalPointer(GL_FLOAT, 0, 0);

	if (this->texture && textid != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers[2]);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
	}

	if (this->texture) {
		glBindTexture(GL_TEXTURE_2D, textid);
		glDrawArrays(GL_TRIANGLES, 0, this->verticeCount);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, this->verticeCount);
	}
}