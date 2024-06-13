// Copyright 2024 Dexter.Wan. All Rights Reserved. 
// EMail: 45141961@qq.com
// Website: https://dt.cq.cn/

#include "DTGdalForUe.h"

#include "cpl_conv.h"
#include "gdal.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"

#define LOCTEXT_NAMESPACE "FDTGdalForUeModule"

void FDTGdalForUeModule::StartupModule()
{
	// DLL path
	FString BaseDir = FPaths::Combine(IPluginManager::Get().FindPlugin("DTGdalForUe")->GetBaseDir(), TEXT("Binaries/ThirdParty/DTGdalForUeLibrary/Win64"));
	TArray<FString> LibraryPath;
	LibraryPath.Add(FPaths::Combine(*BaseDir, TEXT("libcurl.dll")));
	LibraryPath.Add(FPaths::Combine(*BaseDir, TEXT("tiff.dll")));
	LibraryPath.Add(FPaths::Combine(*BaseDir, TEXT("proj_9_4.dll")));
	LibraryPath.Add(FPaths::Combine(*BaseDir, TEXT("libcrypto-1_1-x64.dll")));
	LibraryPath.Add(FPaths::Combine(*BaseDir, TEXT("libssl-1_1-x64.dll")));
	LibraryPath.Add(FPaths::Combine(*BaseDir, TEXT("msodbcsql17.dll")));
	LibraryPath.Add(FPaths::Combine(*BaseDir, TEXT("gdal.dll")));

	// Load dll
	for ( const FString & Path : LibraryPath )
	{
		void * Handle = FPlatformProcess::GetDllHandle(*Path);
		if (Handle != nullptr)
		{
			LibraryHandle.Add(Handle);
		}
		else
		{
			// Load Failure !!!!!
			FMessageDialog::Open(EAppMsgCategory::Error, EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("%s Load Failure !"), *Path)));
			return;
		}
	}

	// Initialize
	const FString GdalPath = GdalResourceDirectory();
	const FString ProjPath = ProjResourceDirectory();
	const std::string szGdalPath = TCHAR_TO_UTF8(*GdalPath);
	const std::string szProjPath = TCHAR_TO_UTF8(*ProjPath);
	CPLSetConfigOption("GDAL_DATA", szGdalPath.c_str());
	CPLSetConfigOption("PROJ_DATA", szProjPath.c_str());
	CPLSetConfigOption("GDAL_ALLOW_LARGE_LIBJPEG_MEM_ALLOC", "YES");
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "YES");
	CPLSetConfigOption("SHAPE_ENCODING", "CP936");
	GDALAllRegister();
}

void FDTGdalForUeModule::ShutdownModule()
{
	for (void * Handle : LibraryHandle)
	{
		FPlatformProcess::FreeDllHandle(Handle);
	}
	LibraryHandle.Empty();
}

FString FDTGdalForUeModule::GdalDirectory()
{
	return FPaths::Combine(FPaths::ConvertRelativePathToFull(IPluginManager::Get().FindPlugin("DTGdalForUe")->GetBaseDir()), TEXT("Binaries/ThirdParty/DTGdalForUeLibrary/Win64"));
}

FString FDTGdalForUeModule::GdalResourceDirectory()
{
	return FPaths::Combine(GdalDirectory(), TEXT("gdal"));
}

FString FDTGdalForUeModule::ProjResourceDirectory()
{
	return FPaths::Combine(GdalDirectory(), TEXT("proj"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDTGdalForUeModule, DTGdalForUe)
