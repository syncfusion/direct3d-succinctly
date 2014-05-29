#pragma once

using namespace Microsoft::WRL;
using namespace Windows::ApplicationModel;
using namespace Windows::Graphics::Display;

// Helper utilities to make Win32 APIs work with exceptions.
namespace DX
{
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			// Set a breakpoint on this line to catch Win32 API errors.
			throw Platform::Exception::CreateException(hr);
		}
	}

	// Reads bytes from the specified file in the current folder
	inline Platform::Array<byte>^ ReadData(_In_ Platform::String^filename)
	{
		CREATEFILE2_EXTENDED_PARAMETERS extendedParams = {0};
		extendedParams.dwSize = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
		extendedParams.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
		extendedParams.dwFileFlags = FILE_FLAG_SEQUENTIAL_SCAN;
		extendedParams.dwSecurityQosFlags = SECURITY_ANONYMOUS;
		extendedParams.lpSecurityAttributes = nullptr;
		extendedParams.hTemplateFile = nullptr;

		Platform::String ^path =Platform::String::Concat(Package::Current->InstalledLocation->Path,"\\");
   
		Wrappers::FileHandle file(CreateFile2(Platform::String::Concat(path, filename)->Data(),
					GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING,	
					&extendedParams));

	if (file.Get() == INVALID_HANDLE_VALUE)
		throw ref new Platform::FailureException();

	FILE_STANDARD_INFO fileInfo = {0};
	if (!GetFileInformationByHandleEx(file.Get(), FileStandardInfo,&fileInfo, sizeof(fileInfo)))
		throw ref new Platform::FailureException();

	if (fileInfo.EndOfFile.HighPart != 0)
		throw ref new Platform::OutOfMemoryException();

	Platform::Array<byte>^ fileData = ref new Platform::Array<byte>(fileInfo.EndOfFile.LowPart);

	if (!ReadFile(file.Get(), fileData->Data, fileData->Length,nullptr, nullptr))
		throw ref new Platform::FailureException();

	return fileData;
 }

}
