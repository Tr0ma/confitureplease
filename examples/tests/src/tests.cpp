#include "tests.h"
#include "s3eInputAdapter.h"
#include <iostream>

using namespace std;

GestureTest::GestureTest()
{
	display = new Display();
	inputAdapater = new s3eInputAdapter();
	gestureManager = new GestureManager(*inputAdapater);

	TapGesture& tap = gestureManager->AddGesture<TapGesture>(*display, &GestureTest::OnTap, *this);
}

GestureTest::~GestureTest()
{
	delete gestureManager;
	delete inputAdapater;
	delete display;
}

void GestureTest::Update(float deltaTime)
{
	gestureManager->Update(deltaTime);
}

Tests::Tests()
{
	test = new GestureTest();
}

Tests::~Tests()
{
	delete test;
}

void Tests::Update(float deltaTime)
{
	test->Update(deltaTime);
}