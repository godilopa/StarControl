#include "../include/map.h"
#include "../include/rectcollision.h"
#include "../include/collision.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"
#include <limits.h>

using namespace rapidxml;

Map::Map(const String &filename, uint16 firstColId) {
	// TAREA: Implementar constructor
	Map::filename = filename;
	Map::firstColId = firstColId;
	valid = false;
	String buffer = String::Read(filename);
	// Analizamos el XML
	xml_document<> doc;
	doc.parse<0>((char*)buffer.ToCString());
	//Obtenemos el nodo raiz map
	xml_node<>* rootNode = doc.first_node();
	String swidth = rootNode->first_attribute("width")->value();
	width = swidth.ToInt();
	String sheight = rootNode->first_attribute("height")->value();
	height = sheight.ToInt();
	String stilewidth = rootNode->first_attribute("tilewidth")->value();
	tileWidth = stilewidth.ToInt();
	String stileheight = rootNode->first_attribute("tileheight")->value();
	tileHeight = stileheight.ToInt();
	//Obtenemos el nodo tileset de map
	xml_node<>* tilesetNode = rootNode->first_node("tileset");
	String sfirstgid = tilesetNode->first_attribute("firstgid")->value();
	int32 firstgid = sfirstgid.ToInt();
	int32 x, y;
	x = y = 0;
	//Obtenemos el nodo offset de tileset
	if (tilesetNode->first_node("tileoffset")){
		xml_node<>* tileoffsetNode = tilesetNode->first_node("tileoffset");
		String x = tileoffsetNode->first_attribute("x")->value();
		x = x.ToInt();
		String y = tileoffsetNode->first_attribute("y")->value();
		y = y.ToInt();
	}
	//Obtenemos el nodo image de tileset
	xml_node<>* imageNode = tilesetNode->first_node("image");
	String source = imageNode->first_attribute("source")->value();
	imageFile = source.StripDir();
	String simagew= imageNode->first_attribute("width")->value();
	int32 imagew = simagew.ToInt();
	String simageh = imageNode->first_attribute("height")->value();
	int32 imageh = simageh.ToInt();

	//Obtenemos el nodo data del nodo layer de map
	xml_node<>* layerNode = rootNode->first_node("layer");
	xml_node<>* dataNode = layerNode->first_node("data");

	if (dataNode->first_attribute("encoding") || dataNode->first_attribute("compression")) throw 0;

	//Rellenamos el tileIds
	xml_node<>* tileNode = dataNode->first_node("tile");
	while (tileNode != nullptr) {
		String sgid = tileNode->first_attribute("gid")->value();
		int32 gid = sgid.ToInt();
		tileIds.Add(gid - firstgid);
		tileNode = tileNode->next_sibling("tile");
	}
	//Carga de la imagen
	image = ResourceManager::Instance().LoadImage(filename.ExtractDir() + "/" + imageFile, imagew / tileWidth, imageh/tileHeight);
	if (tilesetNode->first_node("tileoffset")){
		image->SetHandle(x, y);
	}
	valid = true;
}

void Map::Render() const {
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= 0 ) {
				Renderer::Instance().DrawImage(image, x*GetTileWidth(), y*GetTileHeight(), GetTileId(x, y));
			}
		}
	}
}

bool Map::CheckCollision(const Collision* collision) const {
	// Creamos caja de colisiones
	double boxX = 0, boxY = 0, boxWidth = GetTileWidth(), boxHeight = GetTileHeight();
	RectCollision boxCol(&boxX, &boxY, &boxWidth, &boxHeight);
	
	// Comprobamos colision con cada tile
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= firstColId ) {
				boxX = x * GetTileWidth();
				boxY = y * GetTileHeight();

				if ( collision->DoesCollide(&boxCol) )
					return true;
			}
		}
	}

	return false;
}

double Map::GetGroundY(double x, double y) const {
	double groundY = UINT_MAX;

	if ( x < 0  ||  x >= width*tileWidth  ||  y >= height*tileHeight ) return groundY;
	if ( y < 0 ) y = 0;

	// Buscamos el primer tile en esa columna
	for ( int tiley = int(y/tileHeight); tiley < height; tiley++ ) {
		if ( tileIds[tiley*width + int(x/tileWidth)] >= 0 ) {
			groundY = tiley*tileHeight;
			break;
		}
	}
	return groundY;
}
