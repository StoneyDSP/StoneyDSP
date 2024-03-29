#pragma once

#ifdef RC_INVOKED

#include "stoneydsp_resource.hpp"

// Application icon
IDI_APPICON ICON "stoneydsp.ico"

// Manifest
CREATEPROCESS_MANIFEST_RESOURCE_ID RT_MANIFEST "stoneydsp.manifest"

// Version resource
VS_VERSION_INFO VERSIONINFO
 FILEVERSION STONEYDSP_VERSION_MAJOR,STONEYDSP_VERSION_MINOR,STONEYDSP_VERSION_PATCH,0
 PRODUCTVERSION STONEYDSP_VERSION_MAJOR,STONEYDSP_VERSION_MINOR,STONEYDSP_VERSION_PATCH,0
 FILEFLAGSMASK 0x3fL
#ifdef _DEBUG
 FILEFLAGS VS_FF_DEBUG
#else
#  ifdef STONEYDSP_VERSION_IS_RELEASE
    FILEFLAGS 0x0L
#  else
    FILEFLAGS VS_FF_PRERELEASE
#  endif
#endif

 FILEOS VOS_NT_WINDOWS32
 FILETYPE VFT_APP
 FILESUBTYPE 0x0L
BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040904b0"
        BEGIN
            VALUE "CompanyName", "StoneyDSP"
            VALUE "ProductName", "StoneyDSP"
            VALUE "FileDescription", "StoneyDSP codebase"
            VALUE "FileVersion", STONEYDSP_VERSION
            VALUE "ProductVersion", STONEYDSP_VERSION
            VALUE "OriginalFilename", "stoneydsp.exe"
            VALUE "InternalName", "stoneydsp"
            VALUE "LegalCopyright", "Copyright (c) 2023 Nathan J. Hood. MIT license."
        END
    END
    BLOCK "VarFileInfo"
    BEGIN
        VALUE "Translation", 0x409, 1200
    END
END

#endif
