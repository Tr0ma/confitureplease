#include "Iw2D.h"
#include "tests.h"

#define FRAME_TIME  (30.0f / 1000.0f)

int main()
{
	Iw2DInit();

	Tests* test = new Tests();

	while (!s3eDeviceCheckQuitRequest())
    {
		test->Update(FRAME_TIME);

		Iw2DSurfaceClear(0xff000000);

		test->Render();

		Iw2DSurfaceShow();
		
		s3eDeviceYield(0);
	}

	delete test;

	Iw2DTerminate();

	return 0;
}