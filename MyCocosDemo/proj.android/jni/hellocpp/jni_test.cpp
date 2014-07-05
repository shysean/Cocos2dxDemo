#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "TestCase/JniTest.h"

using namespace cocos2d;

extern "C"
{
    void setPackageName(const char *packageName)
    {
        CCLOG("packageName:%s", packageName);
        
        auto scene = Director::getInstance()->getRunningScene();
        JniTest* jniScene = dynamic_cast<JniTest *>(scene);
        
        if (jniScene) {
            jniScene->setInfo(packageName);
        }
    }
    
    void Java_com_sean_test_jni_JniTest_setPackageName(JNIEnv *env, jobject thiz, jstring packageName)
    {
        const char *pkgName = env->GetStringUTFChars(packageName, NULL);
        setPackageName(pkgName);
        
        env->ReleaseStringUTFChars(packageName, pkgName);
    }
}
