#ifndef UGINE_PIXELCOLLISIONDATA_H
#define	UGINE_PIXELCOLLISIONDATA_H

#include "types.h"
#include "string.h"

extern "C" uint8* stbi_load(const char*, int*, int*, int*, int);

class CollisionPixelData {
public:
	CollisionPixelData(const String& filename) {
		uint8* buffer = stbi_load(filename.ToCString(), &width, &height, nullptr, 4);
		int32 j = 0;
		data = (bool*)malloc(width*height*sizeof(bool));
		for (int32 i = 0; i < 4 * height * width; i += 4) {
			if (buffer[i + 3] == 0){
				data[j] = false;
			}
			else{
				data[j] = true;
			}
			j++;
		}

		delete buffer;
	}

	virtual ~CollisionPixelData() { delete data; };
	virtual bool IsValid() const { return data; };
	virtual const String& GetFilename() const { return filename; };
	virtual uint16 GetWidth() const { return width; };
	virtual uint16 GetHeight() const { return height; };
	virtual bool GetData(uint32 x, uint32 y) const { return data[y*width + x]; }

private:
	String filename;
	int32 width, height;
	bool* data;
};

#endif