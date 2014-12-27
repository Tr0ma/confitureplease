#include "tests.h"
#include "Gesture.h"
#include "s3eInputAdapter.h"

#include <iostream>


using namespace std;

GestureTest::GestureTest()
{
	Display display;
	s3eInputAdapter inputAdapater;
	GestureManager gestureManager(inputAdapater);

	TapGesture& tap = gestureManager.AddGesture<TapGesture>(display, &GestureTest::OnTap, *this);
}

Tests::Tests()
{
	GestureTest test;
}

Tests::~Tests()
{
}

void Tests::Update(float deltaTime)
{
}