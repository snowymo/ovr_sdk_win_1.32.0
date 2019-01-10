/************************************************************************************
Filename    :   Win32_RoomTiny_Main.cpp
Content     :   First-person view test application for Oculus Rift
Created     :   18th Dec 2014
Authors     :   Tom Heath
Copyright   :   Copyright (c) Facebook Technologies, LLC and its affiliates. All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*************************************************************************************/
/// This is the same sample as OculusRoomTiny(DX11), 
/// but this time using the standard set of 
/// utility functions provided in BasicVR.h - these functions we will be
/// used in subsequent samples.

#include "../Common/Win32_DirectXAppUtil.h" // DirectX
#include "../Common/Win32_BasicVR.h"        // Basic VR
#include <string>

void printDouble(std::string name, double d)
{
	std::string str;
	str = name + ":(" + std::to_string(d) + ")\n";
	std::string stemp = std::string(str.begin(), str.end());
	LPCSTR sw = stemp.c_str();
	OutputDebugStringA(sw);
}

void printVector3(std::string name, ovrVector3f v)
{
	std::string str;
	str = name + ":(" + std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z) + ")\n";
	std::string stemp = std::string(str.begin(), str.end());
	LPCSTR sw = stemp.c_str();
	OutputDebugStringA(sw);
}

struct UsingBasicVR : BasicVR
{
    UsingBasicVR(HINSTANCE hinst) : BasicVR(hinst, L"Using BasicVR") {}

    void MainLoop()
    {
	    Layer[0] = new VRLayer(Session);

	    while (HandleMessages())
	    {
			// Query the HMD for ts current tracking state.
			ovrTrackingState ts = ovr_GetTrackingState(Session, ovr_GetTimeInSeconds(), ovrTrue);
			if (ts.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked))
			{
				ovrPosef pose = ts.HeadPose.ThePose;

				printDouble("time", ts.HeadPose.TimeInSeconds);
				//printVector3("AngularVelocity", ts.HeadPose.AngularVelocity);
				//printVector3("AngularAcceleration", ts.HeadPose.AngularAcceleration);
				//printVector3("LinearVelocity", ts.HeadPose.LinearVelocity);
				//printVector3("LinearAcceleration", ts.HeadPose.LinearAcceleration);
			}

			ActionFromInput();
			/*Layer[0]->GetEyePoses();

			for (int eye = 0; eye < 2; ++eye)
			{
				Layer[0]->RenderSceneToEyeBuffer(MainCam, RoomScene, eye);
			}

			Layer[0]->PrepareLayerHeader();
			DistortAndPresent(1);*/
	    }
    }
};

//-------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, int)
{
	UsingBasicVR app(hinst);
    return app.Run();
}
