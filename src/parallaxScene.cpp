#include "../include/parallaxScene.h"
#include "../include/renderer.h"

ParallaxScene::ParallaxScene(Image* imageBack, Image* imageFront){
	backLayer = imageBack;
	frontLayer = imageFront;
	backX = 0;
	backY = 0;
	frontX = 0;
	frontY = 0;
}

void ParallaxScene::Update(double elapsed, Map* map){
	frontX += autoFrontSpeedX * elapsed;
	frontY += autoFrontSpeedY * elapsed;
	backX += autoBackSpeedX * elapsed;
	backY += autoBackSpeedY * elapsed;
	Scene::Update(elapsed, map);
}

void ParallaxScene::RenderBackground() const{
	if (backLayer){
		Renderer::Instance().DrawTiledImage(backLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), GetCamera().GetX()*relBackSpeedX - backX, GetCamera().GetY()*relBackSpeedY - backY);
	}

	if (frontLayer){
		Renderer::Instance().DrawTiledImage(frontLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), GetCamera().GetX()*relFrontSpeedX - frontX, GetCamera().GetY()*relFrontSpeedY - frontY);
	}
}