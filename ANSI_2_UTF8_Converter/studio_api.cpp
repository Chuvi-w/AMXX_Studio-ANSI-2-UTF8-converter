#include "studio_api.h"




int SendStudioMsg(int Message, const CHAR *Data, int IntData)
{
	HWND StudioHandle;
	StudioHandle = FindWindowA("TfrmMain", "AMXX-Studio");
	if (StudioHandle != 0) {		
		COPYDATASTRUCT sMessage;
		sMessage.dwData = IntData;
		sMessage.cbData = strlen(Data) + 1;
		sMessage.lpData = (void *) Data;
		return SendMessage(StudioHandle, WM_COPYDATA, (WPARAM)Message, (LPARAM)&sMessage);
	}
	else
		return -1;
}
