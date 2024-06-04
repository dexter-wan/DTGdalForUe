// Fill out your copyright notice in the Description page of Project Settings.

using System;
using System.IO;
using System.Text;
using UnrealBuildTool;

public class DTGdalForUeLibrary : ModuleRules
{
	private string RelativePath(string absolutePath, string relativeTo)
	{
		string[] absoluteDirectories = absolutePath.Split('\\');
		string[] relativeDirectories = relativeTo.Split('\\');
		
		int length = absoluteDirectories.Length < relativeDirectories.Length ? absoluteDirectories.Length : relativeDirectories.Length;
		int lastCommonRoot = -1;
		int index;

		for (index = 0; index < length; index++)
		{
			if (absoluteDirectories[index] == relativeDirectories[index])
				lastCommonRoot = index;
			else
				break;	
		}

		if (lastCommonRoot == -1)
			throw new ArgumentException("Paths do not have a common base");

		StringBuilder relativePath = new StringBuilder();
		
		for (index = lastCommonRoot + 1; index < absoluteDirectories.Length; index++)
			if (absoluteDirectories[index].Length > 0)
				relativePath.Append("..\\");
		
		for (index = lastCommonRoot + 1; index < relativeDirectories.Length - 1; index++)
			relativePath.Append(relativeDirectories[index] + "\\");
		relativePath.Append(relativeDirectories[relativeDirectories.Length - 1]);

		return relativePath.ToString();
	}
	
	public DTGdalForUeLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		
		// 头文件
		PublicSystemIncludePaths.Add("$(ModuleDir)/Include");
		PublicSystemIncludePaths.Add("$(ModuleDir)/Include/proj");
		PublicSystemIncludePaths.Add("$(ModuleDir)/Include/gdal");
		
		// 链接库
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Lib", "proj.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Lib", "gdal.lib"));

		// 延迟加载DLL
		PublicDelayLoadDLLs.Add("libcurl.dll");
		PublicDelayLoadDLLs.Add("tiff.dll");
		PublicDelayLoadDLLs.Add("proj_9_4.dll");
		PublicDelayLoadDLLs.Add("libcrypto-1_1-x64.dll");
		PublicDelayLoadDLLs.Add("libssl-1_1-x64.dll");
		PublicDelayLoadDLLs.Add("msodbcsql17.dll");
		PublicDelayLoadDLLs.Add("gdal.dll");
		
		// 资源路径
		var binPath = Path.Combine(ModuleDirectory, "Bin");
		
		// 拷贝到插件运行目录
		foreach (var filePath in Directory.GetFiles(binPath, "*", SearchOption.AllDirectories))
		{
			// 拷贝到打包时候的运行目录
			var outPath = Path.Combine("$(PluginDir)/Binaries/ThirdParty/DTGdalForUeLibrary/Win64/", RelativePath(binPath, filePath));
			if ( File.Exists(outPath) )  { File.Delete(outPath); }
			RuntimeDependencies.Add(outPath, filePath);
		}
	}
}
