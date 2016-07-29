#include "../include/mapscene.h"

MapScene::MapScene(Map* map, Image* imageBack, Image* imageFront) : ParallaxScene(imageBack, imageFront) {
	MapScene::map = map;
}

void MapScene::Update(double elapsed) {
	ParallaxScene::Update(elapsed, map);
}

void MapScene::RenderAfterBackground() const {
	map->Render();
}