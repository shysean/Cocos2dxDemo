//
//  XdeltaTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 05/17/14.
//
//

#include "XdeltaTest.h"

extern "C" {		// calling c library must use extern "C"
#include "../Tools/xdelta/xdelta3-internal.h"
}
//extern int xd3_main_cmdline (int argc, char **argv);


// patch(const char *src, const char *dst);
int XdeltaTest::patch(const char *srcFile, const char *patchFile, const char *outFile)
{
	const char *argv[] = {
		"xdelta3",			// command
		"-df",			// d=decompress, f=force overwrite, v=verbose
		"-s",
		srcFile,		// s=source file is:
		patchFile,
		outFile
	};
	
    //    return 0;
	return xd3_main_cmdline(6, (char **) argv);		// 6 = number of argument is six!
}

XdeltaTest::XdeltaTest()
{
    
}

void XdeltaTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}

void XdeltaTest::initTestMenu()
{
    ADD_TEST_METHOD(testFunction);
}



// =============================
//        Test Funtion
// =============================
void XdeltaTest::testFunction()
{
    
    int test = 0;
    char info[1024];
    sprintf(info, "Result = %d", test);
    setInfo(info);
    
//    setInfo("testFunction");
//    
    int result = patch("sss","ddd","ssss");
    
    sprintf(info, "Result = %d", result);
    setInfo(info);
}