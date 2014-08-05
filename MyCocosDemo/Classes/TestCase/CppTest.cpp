//
//  CppTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 06/28/14.
//
//

#include "CppTest.h"

CppTest::CppTest()
{
    
}

void CppTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}

void CppTest::initTestMenu()
{
    ADD_TEST_METHOD(testDestructor);
    ADD_TEST_METHOD(testDoubleDimensionalArray);
    ADD_TEST_METHOD(testBoolValue);
    ADD_TEST_METHOD(testMethodParam1);
    ADD_TEST_METHOD(testAlgorithm1);
    ADD_TEST_METHOD(testAlgorithm2);
    ADD_TEST_METHOD(testAlgorithm3);
    ADD_TEST_METHOD(testByte);
    
}


// =============================
//        Test Funtion
// =============================
void CppTest::testAlgorithm3()
{
    // 由unsigned int(32位: 空白的(8位)+红(8位)+绿(8位)+蓝(8位)) 转换成unsigned short(16位: 红(5位)+绿(6位)+蓝(5位))
    // 0000 0000 0000 0000 0000 0000 0000 0000          0000 0000 0000 0000
    // -         r         g         b                  r     g      b
    
    uint intColor = 0x00332211;
    
    int b = 0x000000FF & intColor;
    int g = 0x0000FF00 & intColor;
    int r = 0x00FF0000 & intColor;
    
    CCLOG("int blue = %d, red = %d, green=%d", b, r >> 16, g >> 8);
    CCLOG("short blue = %d, red = %d, green=%d", b >> 3, r >> 19, g >> 10);
    
    float red = (r >> 16) / (float)0xFF * 256;
    float green = (g >> 8) / (float)0xFF * 256;
    float blue = (b / (float)0xFF) * 256;
    CCLOG("RGB=(%f,%f,%f)", red, green, blue);

    ushort shortColor;
    shortColor |= r >> 19;
    shortColor <<= 6;
    
    shortColor |= g >> 10;
    shortColor <<= 5;

    shortColor |= b >> 3;
    
    r = shortColor & 0xF800;
    g = shortColor & 0x07E0;
    b = shortColor & 0x001F;
    
    red = (r >> 11) / (float)0x1F * 256;
    green = (g >> 5) / (float)0x3F * 256;
    blue = b / (float)0x1F * 256;
    CCLOG("RGB=(%f,%f,%f)", red, green, blue);
//    CCLOG("short blue = %d, red = %d, green=%d", b, r >> 11, g >> 5);
    
    
    
}

// 位域(Bit Field)
struct date_struct {
    int day : 5,       // 1 to 31
    month : 4,      // 1 to 12
    year  : 14;     // 0 to 99
}date;

void CppTest::testByte()
{

    // char b = 5; // 0000(0) 0011(4) 16位0x04;
    
    // # TestCase1:
    // 与运算(&)的一个用途是检查指定位是否置位(等于1)
    // 1 & 1 = 1
    // 1 & 0 = 0
    // 0 & 1 = 0
    // 0 & 0 = 0
    // 0000 0001 (0x01) 检查第一位
    // 0000 0010 (0x04) 检查第二位
    // ...
//    for (int i = 0; i < 32; i++) {
//    
//    if(i & 0x04)
//        {
//            CCLOG("%d Bit two is set!", i);
//        }else
//        {
//            CCLOG("%d Bit two is not set!", i);
//        }
//    }
    
    // # TestCase2:
    // 或运算(|)双目运算。二个位只要有一个位置位，结果就等于1。二个位都为0时，结果为0。
    // 1 | 1 = 1
    // 1 | 0 = 1
    // 0 | 1 = 1
    // 0 | 0 = 0
    // 1  = 0000 0001  0x01
    // 32 = 0001 0000  0x10
    // result = 0001 0001 33
    char result = 1 | 32;
    CCLOG("1 | 32 = %d", result);
    
    
    // #TestCase 3:
    // 异或运算（^）二个位不相等时，结果为1，否则为0。
    // 异或运算可用于位值翻转。例如将第3位与第4位的值翻转：
    // 1 ^ 1 == 0
    // 1 ^ 0 == 1
    // 0 ^ 1 == 1
    // 0 ^ 0 == 0
    // 2 = 0000 0010
    // 3 = 0000 0011
    // result = 0000 0001
    result = 2 ^ 3;
    CCLOG("2^3 = %d", result);
    
    // # TestCase 4:
    // 单目运算，取反值
    // ~0x80 = 0100 0000 第一位符号位
    // result = 1011 1111
    result = ~0x80;
    CCLOG("~~0x80 = %d", result);
    
    // #TestCase 5: 位域
    CCLOG("data size: %lu", sizeof(date));
    
    // 移位运算(>> 与 <<)
    // 0000 1110 14
    // 14 << 3 = 0111 0000
    // 14 >> 3 = 0000 0001
    CCLOG("14 << 3 = %d", 14 << 3);
    CCLOG("14 >> 3 = %d", 14 >> 3);

}
void CppTest::testAlgorithm2()
{
//    查找质数
//    int n = 1370000000;
//    int k = 0;
//    
//    for (int i = 2; i < n; i++){
//    
//        bool isThis = true;
//        for (k = 2; k <= sqrt(i); k++) {
//            if (i%k==0) {
//                isThis = false;
//                break;
//            }
//        }
//        
//        if (isThis) {
//            CCLOG("num = %d", i);
//        }
//    }
    
    
    
    
    for (int i = 1; i <= 100; i ++) {
        
        if (i % 3 != 0 && i % 5 != 0)
        {
            CCLOG("%d", i);
            continue;
        }
        if (i % 3 == 0) {
            CCLOG("Z");
        }
        
        if (i % 5 == 0) {
            CCLOG("N");
        }
        
    }
}

void CppTest::testAlgorithm1()
{
    const char *str = "AAABBBCCDD";
    
    char lastChar = str[0];
    int count = 1;

    std::string result;
    
    while (*str++ != '\0') {
        if (lastChar == *str) {
            count++;
            continue;
        }
        else
        {
            char temp[8];
            sprintf(temp, "%d", count);
            result.append(temp);
            
            sprintf(temp, "%c", lastChar);
            result.append(temp);
            
            count = 1;
            lastChar = *str;
        }
    
    }
    
//    for (int i = 1; i < strlen(str) + 1; i++)
//    {
//        
//
//        if (lastChar == str[i]) {
//            count++;
//            continue;
//        }
//        else
//        {
//            char temp[8];
//            sprintf(temp, "%d", count);
//            result.append(temp);
//            
//            sprintf(temp, "%c", lastChar);
//            result.append(temp);
//            
//            count = 1;
//            lastChar = str[i];
//        }
//    }
    
    CCLOG("result=%s", result.c_str());
}

void CppTest::testBoolValue()
{
    // C++ 中非零值判断为true
    int testValue[] = {-1,0,1,2,3,100};
    
    for (int i: testValue)
    {
        if (i) {
            CCLOG("%d is true", i);
        }else
        {
            CCLOG("%d is false", i);
        }
    }

}

void CppTest::testMethodParam1()
{
    int i = 0;
    int param = 1;
    i = returnParam(param);
    CCLOG("return %d", i);
}




void CppTest::testDestructor()
{
    setInfo("testDestructor");
//
//    CCLOG("----- Test Base Class -----");
//    CppTestBase* a = new CppTestBase();
//    a->doSomething();
//    delete a;
//    
//    CCLOG("----- Test Derived Class -----");
//    CppTestDerived* b = new CppTestDerived();
//    b->doSomething();
//    delete b;
//    
//    CCLOG("----- Test Case 1 -----");
//    CppTestBase *c = new CppTestDerived();
//    c->doSomething();
//    delete c;
    
    A* a = (A*)new B();
    a->print();
    // 143
    
    B* b = (B*)new C();
    b->print();
    // 1479
    
    delete b;
    // 852
    delete a;
    // 2
}

void CppTest::testDoubleDimensionalArray()
{
    int arr1[3];
    int arr2[3];
    int arr3[3];
//    int * ptr;

    // ptr1是一个指向 int [3] 的指针，即ptr的类型和&arr1的类型是一样的，注意：arr1指向的内存区域定长
    int ptr1[3][3]={{1,2,3},{1,2,3},{1,2,3}};
    
    // ptr2是一个指向 int * 的指针，即ptr2的类型和&ptr是一样的，注意：ptr指向的内存区域不定长
    int * ptr2[3]={arr1,arr2,arr3};
    
    // ptr3是一个指向 int [3] 的指针，即ptr3的类型和&arr1的类型是一样的，注意：arr1指向的内存区域定长
    int(* ptr3)[3]=&arr1;
    
    ptr3=ptr1; // 没错，他们的类型相同
    // ptr3=ptr2;//error 无法从“int *[3]”转换为“int (*)[3]
    // ptr4是一个指向 int * 的指针，即ptr4的类型和&ptr是一样的，注意：ptr指向的内存区域不定长
    int ** ptr4;
    //ptr4=&arr1; //error 无法从“int (*)[3]”转换为“int **
    ptr4=ptr2; // 没错，他们的类型相同
    //ptr4=ptr3; // error 无法从“int (*)[3]”转换为“int **
}