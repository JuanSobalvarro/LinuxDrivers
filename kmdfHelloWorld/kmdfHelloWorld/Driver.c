#include <ntddk.h>
#include <wdf.h>

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD KmdfHelloWorldEvtDeviceAdd;

NTSTATUS
DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath
)
{
	// NTSTATUS variable to record if success or failure
	NTSTATUS status = STATUS_SUCCESS;

	// Allocate driver conf object
	WDF_DRIVER_CONFIG config;

	// Print Hello World for DriverEntry
	KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfHelloWorld: DriverEntry\n"));

	// Initialize driver conf object to register entry point for the EvtDeviceAdd callback(KmdfHelloWorldEvtDeviceAdd)
	WDF_DRIVER_CONFIG_INIT(&config, KmdfHelloWorldEvtDeviceAdd);

	// And finally create driver object
	status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &config, WDF_NO_HANDLE);

	return status;
}

NTSTATUS
KmdfHelloWorldEvtDeviceAdd(
	_In_ WDFDRIVER Driver,
	_Inout_ PWDFDEVICE_INIT DeviceInit
)
{
	// We are not using the device object so we need to mark it as unreferenced
	UNREFERENCED_PARAMETER(Driver);

	NTSTATUS status;

	// Allocate device object
	WDFDEVICE hDevice;

	KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "kmdfHelloWorld: KmdfHelloWorldEvtDeviceAdd\n"));

	status = WdfDeviceCreate(&DeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &hDevice);

	return status;
}