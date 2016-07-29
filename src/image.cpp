#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>
#define renderer Renderer::Instance()

//#include "../lib/stb_image.c"
extern "C" uint8* stbi_load(const char*, int*, int*, int*, int );

Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;

	// TAREA: Cargar el buffer de la imagen
	int w, h;
	uint8* buffer = stbi_load(filename.ToCString(), &w, &h, nullptr, 4);
	width = (uint16)w;
	height = (uint16)h;

	//creamos las nuevas dimensiones del buffer
	uint16 newWidth = pow(2, ceil((Log2(width))));
	uint16 newHeight = pow(2, ceil((Log2(height))));

	//comprobamos si la imagen es potencia de 2, sino creamos el espacio para el nuevo buffer de imagen 
	// y lo rellenamos con pixels blancos transparentes
	if (newWidth != width || newHeight != height){
		uint8* newBuffer = (uint8*)malloc(newWidth*newHeight * 4);
		memset(newBuffer, 0, newWidth*newHeight * 4);
		//copiamos el buffer antiguo en el nuevo
		uint8* primeraDireccionB = buffer; //guardamos la primera direccion de buffer para luego volver a colocarlo en su sitio
		uint8* primeraDireccionNB = newBuffer; //guardamos la primera direccion de buffer para luego volver a colocarlo en su sitio
		for (uint16 i = 0; i < height; i++){
			memcpy(newBuffer, buffer, width*4);
			newBuffer = &newBuffer[newWidth*4];
			buffer = &buffer[width * 4];
		}
		buffer = primeraDireccionB;
		newBuffer = primeraDireccionNB;
		primeraDireccionB = nullptr;
		primeraDireccionNB = nullptr;
		free(buffer);
		//generamos la textura del nuevo buffer
		if (newBuffer) {
			// TAREA: Generar la textura de OpenGL
			gltex = renderer.GenImage(newBuffer, newWidth, newHeight);
			free(newBuffer);
		}
		//cambiamos las coordenadas de la nueva imagen para que no pinte el borde blanco
		lastU = (float)width / (float)newWidth;
		lastV = (float)height / (float)newHeight;
	}
	else {

		// Generamos la textura del buffer que era potencia de 2
		if (buffer) {
			// TAREA: Generar la textura de OpenGL
			gltex = renderer.GenImage(buffer, width, height);
			free(buffer);
		}

	}

}

Image::~Image() {
	if(gltex != 0) renderer.DeleteImage(gltex);
}

void Image::Bind() const {
	// TAREA: Establecer la textura actual
	renderer.BindImage(gltex);
}
