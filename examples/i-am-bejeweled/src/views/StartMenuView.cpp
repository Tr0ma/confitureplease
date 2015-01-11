#include "StartMenuView.h"
#include "AtlasTypes.h"

const char* StartMenuView::STARTMENU_VIEW = "StartMenuView_STARTMENU_VIEW";

void StartMenuView::CreateView()
{
	TextureAtlas* atlas = GetAssetManager().GetTextureAtlas(AtlasTypes::MY_ATLAS);
	Image* image = new Image(*(atlas->GetTexture("blue.png")));
	GetContainer().AddChild(*image);
}