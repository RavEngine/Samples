//
//  main.cpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug. All rights reserved.
//

#include "TestApp.h"

#ifdef _WIN32
	#include <Windows.h>
	#include <Xinput.h>
	#pragma comment(lib, "xinput")
	#pragma comment(lib,"Ws2_32")
#endif

START_APP(TestApp)
