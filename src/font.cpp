#include "../include/font.h"

extern "C" uint8* stbi_load(const char*, int*, int*, int*, int);

Font::Font(const String& filename) : Image(filename, 16, 16) {
	for (int32 i = 0; i < 256; i++) {
		glyphs[i].inicioX = 0;
		glyphs[i].inicioY = 0; 
		glyphs[i].offsetX = this->GetWidth();
		glyphs[i].offsetY = this->GetHeight();
	}
	buffer = stbi_load(filename.ToCString(), &w, &h, nullptr, 4);
	TransformarBufferYGuardarGlyph();
}

uint16 Font::GetSize() const {
	return GetHeight();
}

uint32 Font::GetTextWidth(const String& text) const {
	uint32 textWidth = 0;
	for (uint32 i = 0; i < text.Length(); i++) {
		uint32 frame = (int)text[i];
		glyph glyph = glyphs[frame];
		textWidth += glyph.offsetX - glyph.inicioX;
	}
	return textWidth;
}

uint32 Font::GetTextHeight(const String& text) const {
	int32 max = 0;
	for (uint32 i = 0; i < text.Length(); i++){
		uint32 frame = (int)text[i];
		glyph glyph = glyphs[frame];
		int32 aux = glyph.offsetY - glyph.inicioY;
		if (max < aux){
			max = aux;
		}
	}
	return max;
}

void Font::Render(const String& text, double x, double y) const {
	for (uint32 i = 0; i < text.Length(); i++){
		uint32 frame = (int)text[i];
		glyph glyph = glyphs[frame];
		Renderer::Instance().DrawImage(this, x, y, frame);
		x += glyph.offsetX - glyph.inicioX;
	}
}

void Font::TransformarBufferYGuardarGlyph() {
	
	int32 columnaRelativaFrame, filaRelativaFrame, filaTotal, columnaTotal;
	columnaRelativaFrame = filaRelativaFrame = filaTotal = columnaTotal = 0;

	for (int32 i = 0; i < 4 * h * w; i+=4){

		uint8 r = buffer[i];
		uint8 g = buffer[i + 1];
		uint8 b = buffer[i + 2];
		uint8& a = buffer[i + 3];

		if (r == 0 && g == 0 && b == 0) { //Si el pixel es negro lo ponemos transparente
			a = 0;
		}

		if (r == 255 && g == 255 && b == 0) { //Si el pixel es amarillo guardamos sus coordenadas relativas en el glyph que le corresponda segun su fila y columna
			filaRelativaFrame = i / (4*w) % 32;
			columnaRelativaFrame = (i / 4) % 32;
			filaTotal = i / (4 * w * 32) % 16;
			columnaTotal = (i / (4 * 32)) % 16;
			uint32 frame = 16 * filaTotal + columnaTotal;
			glyphs[frame].inicioX = columnaRelativaFrame;
			glyphs[frame].inicioY = filaRelativaFrame;
			a = 0;
		}

		if (r == 255 && g == 0 && b == 0) { //Si el pixel es rojo guardamos sus coordenadas relativas que son las iniciales del glyph
			filaRelativaFrame = i / (4 * w) % 32;
			columnaRelativaFrame = (i / 4) % 32;
			filaTotal = i / (4 * w * 32) % 16;
			columnaTotal = i / (4 * 32) % 16;
			uint32 frame = 16 * filaTotal + columnaTotal;
			glyphs[frame].offsetX = columnaRelativaFrame;
			glyphs[frame].offsetY = filaRelativaFrame;
			a = 0;
		}

	}
		
	//Generamos la nueva imagen con el buffer modificado
	Renderer::Instance().SetImagePixels(buffer, w, h);
	free(buffer); //liberamos la memoria
}