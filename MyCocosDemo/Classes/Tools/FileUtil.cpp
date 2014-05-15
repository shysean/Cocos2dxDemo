//
//  FileUtil.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 5/15/14.
//
//

#include "cocos2d.h"
#include "FileUtil.h"



int FileUtil::copyFile(const char *src, const char *dst) {
	if(src == NULL) {
		return -1;
	}
	
	if(dst == NULL) {
		return -1;
	}
	
	
	// Same location, shouldn't do any copy
	if(strcmp(dst, src) == 0) {
		return -1;
	}
	
    
	//const char* fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(src);
    //)
	ssize_t size;
	unsigned char *data = cocos2d::FileUtils::getInstance()->getFileData(src, "rb", &size);
	
	if (size <= 0) {
		CCLOG("copyFile: fail to read. %s", src);
		return -1;
	}
	
	
	FILE *fp = fopen(dst, "w");
	if(fp == NULL) {
		CCLOG("copyFile: fail to write. %s", dst);
		return -1;
	}
	fwrite(data, size, 1, fp);
	fclose(fp);
	
	return 0;
}