// ****************************************************************
// PacDrive.h header file.
// Author: Ben Baker [headsoft.com.au]
// ****************************************************************
#ifdef PACDRIVE_EXPORTS
#define PACDRIVE_API __declspec(dllexport)
#else
#define PACDRIVE_API __declspec(dllimport)
#endif

#define ID_VENDOR		0xd209	// Ultimarc Vendor Id
#define ID_PAC_UHID		0x1500	// Both PacDrive and U-HID have a PID of 0x15xx
#define ID_ULTRASTIK	0x0500	// UltraStik's have PID of 0x05xx
#define ID_PAC64		0x1400	// Pac64 has a PID of 0x14xx
#define ID_NANOLED		0x1480	// NanoLED has a PID of 0x148x
#define ID_SERVOSTIK	0x1700	// ServoStik has a PID of 0x17xx
#define ID_USBBUTTON	0x1200	// USB Button has a PID of 0x12xx
#define PID_PACDRIVE	0x1500	// PacDrive PID (PacDrive uses it's Version Number to id it's different devices)
#define PID_PACD64_LO	0x1401	// Start of Pac64 PID
#define PID_PACD64_HI	0x1408	// End of Pac64 PID
#define PID_UHID_LO		0x1501	// Start of U-HID PID
#define PID_UHID_HI		0x1508  // End of U-HID PID
#define PID_SERVOSTIK	0x1700  // ServoStik PID
#define PID_USBBUTTON	0x1200	// USB Button PID
#define PID_NANOLED_LO	0x1481	// Start of NanoLED PID
#define PID_NANOLED_HI	0x1484	// End of NaneLED PID
#define PID_IPACIO		0x0410	// I-Pac Ultimate I/O

#define WINDOW_NAME		L"PacDrive.dll Event Window"
#define WINDOW_CLASS	L"PacDrive.dll Event Class"

static GUID GUID_DEVINTERFACE_HID =
{ 0x4D1E55B2L, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } };

typedef struct
{
	UCHAR ReportID;
	UCHAR ReportBuffer[96];
} REPORT_BUF, *PREPORT_BUF;

enum DeviceType
{
	DEVICETYPE_UNKNOWN,
	DEVICETYPE_PACDRIVE,
	DEVICETYPE_UHID,
	DEVICETYPE_PAC64,
	DEVICETYPE_SERVOSTIK,
	DEVICETYPE_USBBUTTON,
	DEVICETYPE_NANOLED,
	DEVICETYPE_IPACIO
};

typedef struct HID_DEVICE_DATA
{
	INT Type;
	HANDLE hDevice;
	USHORT VendorID;
	USHORT ProductID;
	USHORT VersionNumber;
	WCHAR VendorName[256];
	WCHAR ProductName[256];
	WCHAR SerialNumber[256];
	WCHAR DevicePath[256];
	USHORT InputReportLen;
	USHORT OutputReportLen;
	USHORT UsagePage;
	USHORT Usage;
	HID_DEVICE_DATA *pHidDeviceData;
} *PHID_DEVICE_DATA;

typedef VOID (__stdcall *PAC_ATTACHED_CALLBACK)(INT id);
typedef VOID (__stdcall *PAC_REMOVED_CALLBACK)(INT id);

PACDRIVE_API VOID __stdcall PacSetCallbacks(PAC_ATTACHED_CALLBACK pacAttachedCallback, PAC_REMOVED_CALLBACK pacRemovedCallback);

PACDRIVE_API INT __stdcall PacInitialize();
PACDRIVE_API VOID __stdcall PacShutdown();

PACDRIVE_API BOOL __stdcall PacSetLEDStates(INT id, USHORT data);
PACDRIVE_API BOOL __stdcall PacSetLEDState(INT id, INT port, BOOL state);

PACDRIVE_API BOOL __stdcall Pac64SetLEDStates(INT id, INT group, BYTE data);
PACDRIVE_API BOOL __stdcall Pac64SetLEDState(INT id, INT group, INT port, BOOL state);
PACDRIVE_API BOOL __stdcall Pac64SetLEDStatesRandom(INT id);
PACDRIVE_API BOOL __stdcall Pac64SetLEDIntensities(INT id, PBYTE data);
PACDRIVE_API BOOL __stdcall Pac64SetLEDIntensity(INT id, INT port, BYTE intensity);
PACDRIVE_API BOOL __stdcall Pac64SetLEDFadeTime(INT id, BYTE fadeTime);
PACDRIVE_API BOOL __stdcall Pac64SetLEDFlashSpeeds(INT id, BYTE flashSpeed);
PACDRIVE_API BOOL __stdcall Pac64SetLEDFlashSpeed(INT id, INT port, BYTE flashSpeed);
PACDRIVE_API BOOL __stdcall Pac64StartScriptRecording(INT id);
PACDRIVE_API BOOL __stdcall Pac64StopScriptRecording(INT id);
PACDRIVE_API BOOL __stdcall Pac64SetScriptStepDelay(INT id, BYTE stepDelay);
PACDRIVE_API BOOL __stdcall Pac64RunScript(INT id);
PACDRIVE_API BOOL __stdcall Pac64ClearFlash(INT id);
PACDRIVE_API BOOL __stdcall Pac64SetDeviceId(INT id, INT newId);
PACDRIVE_API BOOL __stdcall Pac64UpdateFirmware(INT id);

PACDRIVE_API INT __stdcall PacGetDeviceType(INT id);
PACDRIVE_API INT __stdcall PacGetVendorId(INT id);
PACDRIVE_API INT __stdcall PacGetProductId(INT id);
PACDRIVE_API INT __stdcall PacGetVersionNumber(INT id);
PACDRIVE_API VOID __stdcall PacGetVendorName(INT id, PWCHAR sVendorName);
PACDRIVE_API VOID __stdcall PacGetProductName(INT id, PWCHAR sProductName);
PACDRIVE_API VOID __stdcall PacGetSerialNumber(INT id, PWCHAR sSerialNumber);
PACDRIVE_API VOID __stdcall PacGetDevicePath(INT id, PWCHAR sDevicePath);

PACDRIVE_API BOOL __stdcall PacProgramUHid(INT id, PCHAR sFilePath);

PACDRIVE_API BOOL __stdcall PacSetServoStik4Way();
PACDRIVE_API BOOL __stdcall PacSetServoStik8Way();

PACDRIVE_API BOOL __stdcall USBButtonConfigurePermanent(INT id, PBYTE data);
PACDRIVE_API BOOL __stdcall USBButtonConfigureTemporary(INT id, PBYTE data);
PACDRIVE_API BOOL __stdcall USBButtonConfigureColor(INT id, BYTE red, BYTE green, BYTE blue);
PACDRIVE_API BOOL __stdcall USBButtonGetState(INT id, PBOOL state);

BOOL PacOpen(LPCWSTR devicePath, HID_DEVICE_DATA *pDeviceData);
BOOL PacRead(PHID_DEVICE_DATA pHidDeviceData, PREPORT_BUF pInputReport);
BOOL PacRead(PHID_DEVICE_DATA pHidDeviceData, PREPORT_BUF pInputReport, DWORD timeOut);
BOOL PacWrite(PHID_DEVICE_DATA pHidDeviceData, PREPORT_BUF pOutputReport);
BOOL PacWrite(PHID_DEVICE_DATA pHidDeviceData, PREPORT_BUF pInputReport, DWORD timeOut);

DWORD WINAPI EventWindowThread(LPVOID lpParam);
BOOL RegisterDeviceInterface(HWND hWnd);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL GetDeviceInfo(HANDLE hDevice, USHORT& vendorID, USHORT& productID, USHORT& versionNumber, USHORT& usage, USHORT& usagePage, USHORT& inputReportLen, USHORT& outputReportLen);

void DebugOutput(LPCTSTR lpszFormat, ...);

void strlow(wchar_t *src);
void strlow(char *s);
