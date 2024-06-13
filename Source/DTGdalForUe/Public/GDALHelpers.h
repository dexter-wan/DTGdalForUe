#pragma once

THIRD_PARTY_INCLUDES_START

#include "gdal.h"
#include "gdal_priv.h"
#include "gdal_alg.h"

THIRD_PARTY_INCLUDES_END

#define GDAL_DELETE_FUNCTION(CLASS)			\
CLASS() = delete;							\
CLASS(CLASS &) = delete;					\
CLASS(const CLASS &) = delete;				\
CLASS(CLASS *) = delete;					\
CLASS(const CLASS *) = delete;				\
CLASS(CLASS &&) = delete;					\
CLASS(const CLASS &&) = delete;				\
CLASS& operator = (CLASS&) = delete;		\
CLASS& operator = (const CLASS&) = delete;	\
CLASS& operator = (CLASS*) = delete;		\
CLASS& operator = (const CLASS*) = delete;	\
CLASS& operator = (CLASS&&) = delete;		\
CLASS& operator = (const CLASS&&) = delete;	

class DTGDALFORUE_API GDALUniquePtr
{
private:
	GDALDataset* Object = nullptr;

public:
	// delete the function
	GDAL_DELETE_FUNCTION(GDALUniquePtr)

	// operation function
	GDALUniquePtr(const FString& FileName, bool OpenEx = false);
	GDALUniquePtr(GDALDataset* p) { Object = p; }
	~GDALUniquePtr() { Close(); }
	inline const bool IsValid() const { return Object != nullptr; }
	inline GDALDataset * operator->() const { return Object; }
	inline void Close() { if( Object != nullptr ) { GDALClose(Object); Object = nullptr; } }
};