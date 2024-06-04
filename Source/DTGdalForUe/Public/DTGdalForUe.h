// Copyright 2024 Dexter.Wan. All Rights Reserved. 
// EMail: 45141961@qq.com
// Website: https://dt.cq.cn/

#pragma once

#include "Modules/ModuleManager.h"

class FDTGdalForUeModule : public IModuleInterface
{
	
public:
	// IModuleInterface implementation
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	// gdal run directory
	static FString GdalDirectory();
	// gdal resource directory
	static FString GdalResourceDirectory();
	// proj resource directory
	static FString ProjResourceDirectory();
	
private:
	// Handle to the test dll we will load
	TArray<void*>				LibraryHandle;
};
