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
    
}


// =============================
//        Test Funtion
// =============================
void CppTest::testAlgorithm2()
{
    int n = 137;
    int k = 0;
    
    for (k = 2; k < sqrt(n); k++) {
        if (n%k==0) {
            break;
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