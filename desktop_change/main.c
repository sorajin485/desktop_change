#include <stdio.h>
#include <Windows.h>

int SetMonitorResolution(int monitor, int xRes, int yRes, int depth, int frequecy);

int SetMonitorResolution(int monitor, int xRes, int yRes, int depth, int frequecy)
{
	DEVMODE             deviceMode;
	DISPLAY_DEVICE      displayDevice;
	memset(&displayDevice, 0, sizeof(DISPLAY_DEVICE));
	memset(&deviceMode, 0, sizeof(DEVMODE));
	displayDevice.cb = sizeof(displayDevice);

	//i번째 모니터의 디바이스 정보를 얻어옴
	EnumDisplayDevices(NULL, monitor, &displayDevice, 0);
	//디바이스 이름을 가지고 현재 화면 정보를 얻음
	EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &deviceMode);

	// 해상도를 바꿈
	deviceMode.dmBitsPerPel = depth; // 픽셀당 비트수
	deviceMode.dmPelsWidth = xRes;
	deviceMode.dmPelsHeight = yRes;
	deviceMode.dmDisplayFrequency = frequecy; //주파수
	deviceMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	
	//ChangeDisplaySettingsEx 반환값 DISP_CHANGE_SUCCESSFUL은 설정이 변경되었다는 반환값
	//CDS_TEST 가 매개변수에 들어가면 응용프로그램이 시스템을 변경하지 않고 실제로 유효한 그래픽 모드를 판별할수 있다. 즉 변경이 가능한지 알아보는 단계
	//3번째 5번째 인자 고정 NULL
	if (ChangeDisplaySettingsEx(displayDevice.DeviceName, &deviceMode, NULL, CDS_TEST, NULL) == DISP_CHANGE_SUCCESSFUL)
	{
		printf("해상도 변경 가능 : \n");
		ChangeDisplaySettingsEx(displayDevice.DeviceName, &deviceMode, NULL, 0, NULL);
	}
	else
		return 2;
	return 1;
}
int main()
{
	SetMonitorResolution(0, 1920, 1080, 32, 60);
	return 0;
}