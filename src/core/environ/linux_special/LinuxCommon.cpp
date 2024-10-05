#include "minizip/unzip.h"
#include "zlib.h"
#include <map>
#include <string>
#include <vector>
#include "tjs.h"
#include "MsgIntf.h"
#include "md5.h"
#include "DebugIntf.h"
#include <condition_variable>
#include <mutex>
#include <set>
#include <sstream>
#include "SysInitIntf.h"
#include "platform/CCFileUtils.h"
#include "ConfigManager/LocaleConfigManager.h"
#include "Platform.h"
#include "platform/CCCommon.h"
#include <EGL/egl.h>
#include <queue>
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include <unistd.h>
#include <fcntl.h>
#include "TickCount.h"
#include "StorageImpl.h"
#include "ConfigManager/IndividualConfigManager.h"
#include "EventIntf.h"
#include "RenderManager.h"
#include <sys/stat.h>
#include "deprecated/CCString.h"

USING_NS_CC;

#define KR2ActJavaPath "org/tvp/kirikiri2n/KR2Activity"
//#define KR2EntryJavaPath "org/tvp/kirikiri2/Kirikiroid2"

extern unsigned int __page_size = getpagesize();

void TVPPrintLog(const char *str) {
	// __android_log_print(ANDROID_LOG_INFO, "kr2 debug info", "%s", str);
}

static tjs_uint32 _lastMemoryInfoQuery = 0;
static tjs_int _availMemory, _usedMemory;
static void _updateMemoryInfo() {
	if (TVPGetRoughTickCount32() - _lastMemoryInfoQuery > 3000) { // freq in 3s
	}
}

tjs_int TVPGetSystemFreeMemory()
{
	_updateMemoryInfo();
	return _availMemory;
}

tjs_int TVPGetSelfUsedMemory()
{
	_updateMemoryInfo();
	return _usedMemory;
}

void TVPForceSwapBuffer() {
	eglSwapBuffers(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW));
}

std::string TVPGetDeviceID()
{
    std::string ret;
    return ret;
}


static std::string GetApkStoragePath() {
}

static std::string GetPackageName() {
}

// from unzip.cpp
#define FLAG_UTF8 (1<<11)
extern zlib_filefunc64_def TVPZlibFileFunc;
class ZipFile
{
	unzFile uf;
	bool utf8;

public:
	ZipFile() : uf(0) {
	}
	~ZipFile() {
		if (uf) {
			unzClose(uf);
			uf = NULL;
		}
	}
    bool Open(const char *filename) {
        if ((uf = unzOpen(filename)) == NULL) {
            ttstr msg = filename;
            msg += TJS_W(" can't open.");
            TVPThrowExceptionMessage(msg.c_str());
            return false;
        }
        // UTF8なファイル名かどうかの判定。最初のファイルで決める
        unzGoToFirstFile(uf);
        unz_file_info file_info;
        if (unzGetCurrentFileInfo(uf, &file_info, NULL, 0, NULL, 0, NULL, 0) == UNZ_OK) {
            utf8 = (file_info.flag & FLAG_UTF8) != 0;
            return true;
        }
        return false;
    }
	bool GetData(std::vector<unsigned char> &buff, const char *filename) {
		bool ret = false;
		if (unzLocateFile(uf, filename, 1) == UNZ_OK) {
			int result = unzOpenCurrentFile(uf);
			if (result == UNZ_OK) {
				unz_file_info info;
				unzGetCurrentFileInfo(uf, &info, NULL, 0, NULL, 0, NULL, 0);
				buff.resize(info.uncompressed_size);
				unsigned int size = unzReadCurrentFile(uf, &buff[0], info.uncompressed_size);
				if (size == info.uncompressed_size) ret = true;
				unzCloseCurrentFile(uf);
			}
		}
		return ret;
	}
    tjs_int64 GetMD5InZip(const char *filename) {
        std::vector<unsigned char> buff;
        if(!GetData(buff, filename)) return 0;
        md5_state_t state;
        md5_init(&state);
        md5_append(&state, (const md5_byte_t*)&buff[0], buff.size());
        union {
            tjs_int64 _s64[2];
            tjs_uint8 _u8[16];
        } digest;
        md5_finish(&state, digest._u8);
        return digest._s64[0] ^ digest._s64[1];
    }
private:
	unzFile zipFile;
};

std::string TVPGetDeviceLanguage() {return "";}

std::string TVPGetPackageVersionString() {
	return "";
}

static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.emplace_back(item);
	}
	return elems;
}


static std::string GetInternalStoragePath() {
    return "";
}


std::string Android_GetDumpStoragePath() {
	return GetInternalStoragePath() + "/dump";
}


static int GetExternalStoragePath(std::vector<std::string> &ret) {
	int count = 0;
	return count;
}

std::vector<std::string> TVPGetAppStoragePath() {
	std::vector<std::string> ret;
	ret.emplace_back(GetInternalStoragePath());
	GetExternalStoragePath(ret);
	return ret;
}

std::vector<std::string> TVPGetDriverPath() {
	std::vector<std::string> ret;
	return ret;
}

namespace kr2android {
    std::condition_variable MessageBoxCond;
	std::mutex MessageBoxLock;
	int MsgBoxRet = -2;
	std::string MessageBoxRetText;
}
using namespace kr2android;

int TVPShowSimpleMessageBox(const char *pszText, const char *pszTitle, unsigned int nButton, const char **btnText) {
	return -1;
}

int TVPShowSimpleMessageBox(const ttstr & text, const ttstr & caption, const std::vector<ttstr> &vecButtons) {
	tTJSNarrowStringHolder pszText(text.c_str());
	tTJSNarrowStringHolder pszTitle(caption.c_str());
	std::vector<const char *> btnText; btnText.reserve(vecButtons.size());
	std::vector<std::string> btnTextHold; btnTextHold.reserve(vecButtons.size());
	for (const ttstr &btn : vecButtons) {
		btnTextHold.emplace_back(btn.AsStdString());
		btnText.emplace_back(btnTextHold.back().c_str());
	}
	return TVPShowSimpleMessageBox(pszText, pszTitle, btnText.size(), &btnText[0]);
}

int TVPShowSimpleInputBox(ttstr &text, const ttstr &caption, const ttstr &prompt, const std::vector<ttstr> &vecButtons) {
	return -1;
}

extern std::string Android_ShowInputDialog(const char* pszTitle, const char *pszInitText);
extern std::string Android_ShowFileBrowser(const char* pszTitle, const char *pszInitDir, bool showEditor);
extern ttstr TVPGetAppPath();
extern ttstr TVPGetLocallyAccessibleName(const ttstr &name);

std::vector<ttstr> Android_GetExternalStoragePath() {
	static std::vector<ttstr> ret;
	if (ret.empty()) {
		std::vector<std::string> pathlist;
		GetExternalStoragePath(pathlist);
		for (const std::string &path : pathlist) {
			std::string strPath = "file://.";
			strPath += path;
			ret.emplace_back(strPath);
		}
	}
	return ret;
}

ttstr Android_GetInternalStoragePath() {
	static ttstr strPath;
	if (strPath.IsEmpty()) {
		strPath = "file://.";
		strPath += GetInternalStoragePath();
	}
	return strPath;
}

ttstr Android_GetApkStoragePath() {
	static ttstr strPath;
	if (strPath.IsEmpty()) {
		strPath = "file://.";
		strPath += GetApkStoragePath();
	}
	return strPath;
}
#if 0
struct _eventQueueNode {
	std::function<void()> func;
	_eventQueueNode *prev;
	_eventQueueNode *next;
};

static std::atomic<_eventQueueNode*> _lastQueuedEvents(nullptr);
static void _processEvents(float) {
	_eventQueueNode* q = _lastQueuedEvents.exchange(nullptr);
	if (q) {
		q->next = nullptr;
		while (q->prev) {
			q->prev->next = q;
			q = q->prev;
		}
	}
	while (q) {
		q->func();
		_eventQueueNode *nq = q->next;
		delete q;
		q = nq;
	}
}

void Android_PushEvents(const std::function<void()> &func) {
	_eventQueueNode *node = new _eventQueueNode;
	node->func = func;
	node->next = nullptr;
	node->prev = nullptr;
	while (!_lastQueuedEvents.compare_exchange_weak(node->prev, node)) {}
}
#endif
void TVPCheckAndSendDumps(const std::string &dumpdir, const std::string &packageName, const std::string &versionStr);
bool TVPCheckStartupArg() {
	// check dump
	TVPCheckAndSendDumps(Android_GetDumpStoragePath(), GetPackageName(), TVPGetPackageVersionString());
#if 0
	// register event dispatcher
	cocos2d::Director *director = cocos2d::Director::getInstance();
	class HackForScheduler : public cocos2d::Scheduler {
	public:
		void regProcessEvents() {
			schedulePerFrame(_processEvents, &_lastQueuedEvents, -1, false);
		}
	};
	static_cast<HackForScheduler*>(director->getScheduler())->regProcessEvents();
#endif
	return false;
}


void Android_PushEvents(const std::function<void()> &func) {
	cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread(func);
}


// TODO: implement following functions

void TVPControlAdDialog(int adType, int arg1, int arg2) {

}

static int _GetAndroidSDKVersion() {
    return 0;
}
static int GetAndroidSDKVersion() {
	static int result = _GetAndroidSDKVersion();
	return result;
}

static bool IsLollipop() {
	return GetAndroidSDKVersion() >= 21;
}

static bool IsOreo() {
	return GetAndroidSDKVersion() >= 26;
}

void TVPFetchSDCardPermission() {
	if (!IsLollipop())
		return;
	return;
}

bool TVPCheckStartupPath(const std::string &path) {
	// check writing permission first
	return true;
}

bool TVPCreateFolders(const ttstr &folder)
{
	return false;
}

static bool TVPWriteDataToFileJava(const std::string &filename, const void* data, unsigned int size) {
	return false;
}

bool TVPWriteDataToFile(const ttstr &filepath, const void *data, unsigned int size) {
	std::string filename = filepath.AsStdString();
	cocos2d::FileUtils *fileutil = cocos2d::FileUtils::getInstance();
	while (fileutil->isFileExist(filename)) {
		// for number filename suffix issue
		time_t t = time(nullptr);
		std::vector<char> buffer;
		buffer.resize(filename.size() + 32);
		sprintf(&buffer.front(), "%s.%d.bak", filename.c_str(), (int)t);
		std::string tempname = &buffer.front();
		if (rename(filename.c_str(), tempname.c_str()) == 0) {
			// file api is OK
			FILE *fp = fopen(filename.c_str(), "wb");
			if (fp) {
				bool ret = fwrite(data, 1, size, fp) == size;
				fclose(fp);
				remove(tempname.c_str());
				return ret;
			}
		}
		bool ret = TVPWriteDataToFileJava(filename, data, size);
		if (fileutil->isFileExist(tempname.c_str())) {
			TVPDeleteFile(tempname);
		}
		return ret;
	}
	FILE *fp = fopen(filename.c_str(), "wb");
	if (fp) {
		// file api is OK
		int writed = fwrite(data, 1, size, fp);
		fclose(fp);
		return writed == size;
	}
	return TVPWriteDataToFileJava(filename, data, size);
}

std::string TVPGetCurrentLanguage() {
	return "";
}

void TVPExitApplication(int code) {
	exit(code);
}

void TVPHideIME() {

}

void TVPShowIME(int x, int y, int w, int h) {

}

void TVPProcessInputEvents() {}

bool TVPDeleteFile(const std::string &filename) {

	return false;
}

bool TVPRenameFile(const std::string &from, const std::string &to) {

	return false;
}

tjs_uint32 TVPGetRoughTickCount32()
{
	tjs_uint32 uptime = 0;
	struct timespec on;
	if (clock_gettime(CLOCK_MONOTONIC, &on) == 0)
		uptime = on.tv_sec * 1000 + on.tv_nsec / 1000000;
	return uptime;
}

bool TVP_stat(const tjs_char *name, tTVP_stat &s) {
	tTJSNarrowStringHolder holder(name);
	return TVP_stat(holder, s);
}

#undef st_atime
#undef st_ctime
#undef st_mtime
//int stat64(const char* __path, struct stat64* __buf) __INTRODUCED_IN(21); // force link it !
bool TVP_stat(const char *name, tTVP_stat &s) {
	struct stat t;
	// static_assert(sizeof(t.st_size) == 4, "");
	static_assert(sizeof(t.st_size) == 8, "");
	bool ret = !stat(name, &t);
	s.st_mode = t.st_mode;
	s.st_size = t.st_size;
	s.st_atime = t.st_atim.tv_sec;
	s.st_mtime = t.st_mtim.tv_sec;
	s.st_ctime = t.st_ctim.tv_sec;
	return ret;
}

void TVPSendToOtherApp(const std::string &filename) {

}
