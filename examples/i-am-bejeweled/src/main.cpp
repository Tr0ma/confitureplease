#include "Iw2D.h"
#include "Context.h"
#include "GameConfig.h"

#define FRAME_TIME  (30.0f / 1000.0f)

int main()
{
	Iw2DInit();

	Context* context = new Context();
	GameConfig* config = new GameConfig();
	context->Configure(*config);
	context->Execute();

	while (!s3eDeviceCheckQuitRequest())
    {
		context->Update(FRAME_TIME);

		Iw2DSurfaceClear(0xff000000);

		context->Render();

		Iw2DSurfaceShow();
		
		s3eDeviceYield(0);
	}

	delete context;
	delete config;
	

	Iw2DTerminate();

	return 0;
}