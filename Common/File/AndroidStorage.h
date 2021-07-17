#pragma once

#include <vector>
#include <string>

#include "Common/File/DirListing.h"

// To emphasize that Android storage mode strings are different, let's just use
// an enum.
enum class Android_OpenContentUriMode {
	READ = 0,  // "r"
	READ_WRITE = 1,  // "rw"
	READ_WRITE_TRUNCATE = 2,  // "rwt"
};

#if PPSSPP_PLATFORM(ANDROID) && !defined(__LIBRETRO__)

#include <jni.h>

extern std::string g_extFilesDir;

void Android_StorageSetNativeActivity(jobject nativeActivity);

bool Android_IsContentUri(const std::string &uri);
int Android_OpenContentUriFd(const std::string &uri, const Android_OpenContentUriMode mode);
bool Android_CreateDirectory(const std::string &parentTreeUri, const std::string &dirName);
bool Android_CreateFile(const std::string &parentTreeUri, const std::string &fileName);
bool Android_RemoveFile(const std::string &fileUri);
bool Android_GetFileInfo(const std::string &fileUri, File::FileInfo *info);
int64_t Android_GetFreeSpaceByContentUri(const std::string &uri);
int64_t Android_GetFreeSpaceByFilePath(const std::string &filePath);
bool Android_IsExternalStoragePreservedLegacy();

std::vector<File::FileInfo> Android_ListContentUri(const std::string &uri);

void Android_RegisterStorageCallbacks(JNIEnv * env, jobject obj);

#else

// Stub out the Android Storage wrappers, so that we can avoid ifdefs everywhere.

inline bool Android_IsContentUri(const std::string &uri) { return false; }
inline int Android_OpenContentUriFd(const std::string &uri, const Android_OpenContentUriMode mode) { return -1; }
inline bool Android_CreateDirectory(const std::string &parentTreeUri, const std::string &dirName) { return false; }
inline bool Android_CreateFile(const std::string &parentTreeUri, const std::string &fileName) { return false; }
inline bool Android_RemoveFile(const std::string &fileUri) { return false; }
inline bool Android_GetFileInfo(const std::string &fileUri, File::FileInfo *info) { return false; }
inline int64_t Android_GetFreeSpaceByContentUri(const std::string &uri) { return -1; }
inline int64_t Android_GetFreeSpaceByFilePath(const std::string &filePath) { return -1; }
inline bool Android_IsExternalStoragePreservedLegacy() { return false; }
inline std::vector<File::FileInfo> Android_ListContentUri(const std::string &uri) {
	return std::vector<File::FileInfo>();
}

#endif
