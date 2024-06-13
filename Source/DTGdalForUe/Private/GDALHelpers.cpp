#include "GDALHelpers.h"

GDALUniquePtr::GDALUniquePtr(const FString& FileName, bool OpenEx)
{
	const TCHAR* pszFileName = *FileName;
	if ( OpenEx )
	{
		Object = (GDALDataset*)GDALOpenEx(TCHAR_TO_UTF8(pszFileName), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
	}
	else
	{
		Object = (GDALDataset*)GDALOpen(TCHAR_TO_UTF8(pszFileName), GA_ReadOnly);
	}
}