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

	//i��° ������� ����̽� ������ ����
	EnumDisplayDevices(NULL, monitor, &displayDevice, 0);
	//����̽� �̸��� ������ ���� ȭ�� ������ ����
	EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &deviceMode);

	// �ػ󵵸� �ٲ�
	deviceMode.dmBitsPerPel = depth; // �ȼ��� ��Ʈ��
	deviceMode.dmPelsWidth = xRes;
	deviceMode.dmPelsHeight = yRes;
	deviceMode.dmDisplayFrequency = frequecy; //���ļ�
	deviceMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	
	//ChangeDisplaySettingsEx ��ȯ�� DISP_CHANGE_SUCCESSFUL�� ������ ����Ǿ��ٴ� ��ȯ��
	//CDS_TEST �� �Ű������� ���� �������α׷��� �ý����� �������� �ʰ� ������ ��ȿ�� �׷��� ��带 �Ǻ��Ҽ� �ִ�. �� ������ �������� �˾ƺ��� �ܰ�
	//3��° 5��° ���� ���� NULL
	if (ChangeDisplaySettingsEx(displayDevice.DeviceName, &deviceMode, NULL, CDS_TEST, NULL) == DISP_CHANGE_SUCCESSFUL)
	{
		printf("�ػ� ���� ���� : \n");
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