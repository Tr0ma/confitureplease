#include "StartMenuView.h"
#include "AtlasTypes.h"

const char* StartMenuView::ID = "StartMenuView_ID";

StartMenuView::~StartMenuView()
{
	GetContainer().RemoveChild(*image);
	delete image;
}

void StartMenuView::CreateView()
{
	TextureAtlas* atlas = GetAssetManager().GetTextureAtlas(AtlasTypes::MY_ATLAS);
	image = new Image(*(atlas->GetTexture("blue.png")));
	GetContainer().AddChild(*image);
}