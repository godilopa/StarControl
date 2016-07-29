#ifndef FONT_H
#define FONT_H

#include "image.h"
#include "glyph.h"
#include "types.h"

class Font : public Image {
public:
	Font(const String& filename);
	virtual uint16 GetSize() const;
	virtual uint32 GetTextWidth(const String& text) const;
	virtual uint32 GetTextHeight(const String& text) const;
	virtual void Render(const String& text, double x, double y) const;
private:
	void TransformarBufferYGuardarGlyph();
	glyph glyphs[256];
	uint8* buffer;
	int32 w, h;
};

#endif
