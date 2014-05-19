//
//  ResourceTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 05/13/14.
//
//
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>

#include "ResourceTest.h"
#include "../Tools/UIUtil.h"
#include "../Tools/StringUtil.h"
#include "../Tools/TimeUtil.h"
#include "../Tools/FileUtil.h"
#include "base64.h"

using namespace std;

ResourceTest::ResourceTest()
{
    
}

void ResourceTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}

void ResourceTest::initTestMenu()
{
    ADD_TEST_METHOD(testStringBase64);
    ADD_TEST_METHOD(testPngBase64);
    ADD_TEST_METHOD(testCreateSpriteWithFileData);
    ADD_TEST_METHOD(testCreateSpriteWithStringData);
    ADD_TEST_METHOD(testReadIndexFile);
    ADD_TEST_METHOD(testCreateSpriteWithBinFile);
    
    ADD_TEST_METHOD(testTexturePacker);
}


struct IndexFile
{
    std::string filename;
    int offset;
    int size;
    
    IndexFile(std::string content)
    {
        vector<string> token;
        StringUtil::split(content, ',', token);
        
        filename = token.at(0);
        offset = StringUtil::intValue(token.at(1).c_str(), 0);
        size = StringUtil::intValue(token.at(2).c_str(), 0);
    }
    
    std::string info()
    {
        char info[1024];
        sprintf(info, "filename=%s offset=%d size=%d", filename.c_str(), offset, size);
        return info;
    }
};


void ResourceTest::showImageUsingData(unsigned char *data, unsigned long dataSize)
{
	if(data == NULL) {
		CCLOG("ResourceTest: data is null");
		return;
	}
	
	CCLOG("ResourceTest: data has read. size=%ld", dataSize);
	
	CCLOG("%s", data);
	Image* image = new Image();
	bool flag;
//	flag = image->initWithImageData(data, dataSize, Image::Format::PNG);
    flag = image->initWithImageData(data, dataSize);
	CCLOG("ResourceTest: CCImage flag=%d", flag);
	
//	Director::getInstance()->getTextureCache()->addImage(image, "testImage");
	
	Texture2D* texture = new Texture2D();
	flag = texture->initWithImage(image);
	CCLOG("ResourceTest: Texture2D flag=%d", flag);
	
	Sprite* sprite = Sprite::create();
	sprite->setTexture(texture);
	
    
    Rect rect = Rect::ZERO;
    rect.size = texture->getContentSize();
    sprite->setTextureRect(rect);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    int x = rand()%(int)visibleSize.width;
    int y = rand()%(int)visibleSize.height;
    sprite->setPosition(Point(x, y));
	addChild(sprite);


}

// =============================
//        Test Funtion
// =============================

void ResourceTest::testReadIndexFile()
{
    // src
    const char* srcIndexFile = "png.idx";
    std::string fullSrcIndexFile = FileUtils::getInstance()->fullPathForFilename(srcIndexFile);
    
    // dst
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string indexFile = writablePath + srcIndexFile;
    
    // copy to writablePath
    FileUtil::copyFile(fullSrcIndexFile.c_str(), indexFile.c_str());
    
    // sean: do {}while(0) 防御式风格
    do
    {
        CC_BREAK_IF(FileUtils::getInstance()->isFileExist(indexFile) == false);
        
        std::string content = FileUtils::getInstance()->getStringFromFile(indexFile);
        CCLOG("%s", content.c_str());
        
        std::vector<string> lines;
        StringUtil::split(content, '\n', lines);
        
        std::vector<IndexFile *> vectorOfIndexFile;
        for (string line: lines)
        {
//            CCLOG("%s", line.c_str());
            IndexFile* indexFile = new IndexFile(line);
            CCLOG("%s", indexFile->info().c_str());
            vectorOfIndexFile.push_back(indexFile);
        }
        
        char info[1024];
        sprintf(info, "Total File = %lu Detail see console.", vectorOfIndexFile.size());
        setInfo(info);
        
    }while (0);
}

void ResourceTest::testCreateSpriteWithBinFile()
{
    
    // src
    const char* srcIndexFile = "png.idx";
    const char* srcBinFile = "png.bin";
    std::string fullSrcIndexFile = FileUtils::getInstance()->fullPathForFilename(srcIndexFile);
    std::string fullSrcBinFile = FileUtils::getInstance()->fullPathForFilename(srcBinFile);

    // dst
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string indexFile = writablePath + srcIndexFile;
    std::string binFile = writablePath + srcBinFile;
    
    // copy to writablePath
    FileUtil::copyFile(fullSrcIndexFile.c_str(), indexFile.c_str());
    FileUtil::copyFile(fullSrcBinFile.c_str(), binFile.c_str());
    
    
    if(FileUtils::getInstance()->isFileExist(indexFile) == false)
    {
        CCLOGWARN("File not exist!");
        return;
    }

    long long startTime = TimeUtil::currentTimeMillis();

    std::string content = FileUtils::getInstance()->getStringFromFile(indexFile);
    
    std::vector<string> lines;
    StringUtil::split(content, '\n', lines);
    
    std::vector<IndexFile *> vectorOfIndexFile;
    for (string line: lines)
    {
        IndexFile* indexFile = new IndexFile(line);
        vectorOfIndexFile.push_back(indexFile);
    }
    
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(binFile);
    const char* fullPathBinFile = fullPath.c_str();
    
    CCLOG("BinFile: %s", fullPathBinFile);
    
    // sean: ifstream can not read within the zip file.
    //       Assets are stored within the apk, a zip file.
    //       so, copy the file from assets to writeable path,
    //       then read. @see beginning of this method
    std::ifstream fin(fullPathBinFile, std::ios::in |std::ios::binary);
    
    // debug info for Android!
    bool isOpen = fin.is_open();
    isOpen ? CCLOG("BinFile has Opened!") : CCLOG("BinFile not opened!");
    
    if (isOpen == false)
    {
        CCLOGWARN("%s File not exist!", fullPathBinFile);
        return;
    }
    
    for (IndexFile *f: vectorOfIndexFile)
    {
        CCLOG("%s", f->info().c_str());
        char* png = (char*) malloc(f->size);
        
        fin.seekg(f->offset);
        fin.read(png, f->size);
        
        CCLOG("%s", png);

        unsigned char *decodeData;
        int dataSize = base64Decode((unsigned char*)png, f->size, &decodeData);
        
        showImageUsingData(decodeData, dataSize);
        
    }
    
    fin.close();
    
    long long endTime = TimeUtil::currentTimeMillis();
    
    char info[1024];
    sprintf(info, "Time consuming = %lld", endTime - startTime);
    setInfo(info);
}

void ResourceTest::testStringBase64()
{
    
    std::string data = "HELLO BASE64";

    char* encodedData = 0;
    base64Encode((unsigned char*)data.c_str(), data.length(), &encodedData);

    unsigned char *decodeData;
    int inSize = strlen(encodedData);
    
    int outSize = base64Decode((unsigned char*)encodedData, (unsigned int)strlen(encodedData), &decodeData);
    
    char info[1024];
    sprintf(info, "String=%s Encoded=%s Decode=%s in/out:%d,%d", data.c_str(), encodedData, decodeData, inSize, outSize);
    CCLOG("%s,Lenth = %d",(const char*)decodeData, outSize);
    
    setInfo(info);

}

void ResourceTest::testPngBase64()
{
    const char* pngFile = "CloseSelected.png";
    Data fileData = FileUtils::getInstance()->getDataFromFile(pngFile);

    char *encodedData = 0;
    int encodeLen = base64Encode(fileData.getBytes(), fileData.getSize(), &encodedData);
    CCLOG("%s,%d",encodedData, encodeLen);
    
    char info[1024];
    sprintf(info, "encode data size = %d", encodeLen);
    setInfo(info);
}

void ResourceTest::testCreateSpriteWithFileData()
{
    const char* pngFile = "CloseSelected.png";
    
//    sean: 2 way to get file data to create image.
//    
//    #1
//    ssize_t dataSize = 0;
//    unsigned char* fileData = FileUtils::getInstance()->getFileData(pngFile, "rb", &dataSize);
//    showImageUsingData(fileData, dataSize);

//    #2
    Data fileData = FileUtils::getInstance()->getDataFromFile(pngFile);
    showImageUsingData(fileData.getBytes(), fileData.getSize());
    long long startTime = TimeUtil::currentTimeMillis();

    long long endTime = TimeUtil::currentTimeMillis();
    
    char info[1024];
    sprintf(info, "run time = %lld", endTime - startTime);
    setInfo(info);
}

void ResourceTest::testCreateSpriteWithStringData()
{
    // generate by python
    const char* data = "iVBORw0KGgoAAAANSUhEUgAAACgAAAAoCAYAAACM/rhtAAAACXBIWXMAAAsTAAALEwEAmpwYAAAKT2lDQ1BQaG90b3Nob3AgSUNDIHByb2ZpbGUAAHjanVNnVFPpFj333vRCS4iAlEtvUhUIIFJCi4AUkSYqIQkQSoghodkVUcERRUUEG8igiAOOjoCMFVEsDIoK2AfkIaKOg6OIisr74Xuja9a89+bN/rXXPues852zzwfACAyWSDNRNYAMqUIeEeCDx8TG4eQuQIEKJHAAEAizZCFz/SMBAPh+PDwrIsAHvgABeNMLCADATZvAMByH/w/qQplcAYCEAcB0kThLCIAUAEB6jkKmAEBGAYCdmCZTAKAEAGDLY2LjAFAtAGAnf+bTAICd+Jl7AQBblCEVAaCRACATZYhEAGg7AKzPVopFAFgwABRmS8Q5ANgtADBJV2ZIALC3AMDOEAuyAAgMADBRiIUpAAR7AGDIIyN4AISZABRG8lc88SuuEOcqAAB4mbI8uSQ5RYFbCC1xB1dXLh4ozkkXKxQ2YQJhmkAuwnmZGTKBNA/g88wAAKCRFRHgg/P9eM4Ors7ONo62Dl8t6r8G/yJiYuP+5c+rcEAAAOF0ftH+LC+zGoA7BoBt/qIl7gRoXgugdfeLZrIPQLUAoOnaV/Nw+H48PEWhkLnZ2eXk5NhKxEJbYcpXff5nwl/AV/1s+X48/Pf14L7iJIEyXYFHBPjgwsz0TKUcz5IJhGLc5o9H/LcL//wd0yLESWK5WCoU41EScY5EmozzMqUiiUKSKcUl0v9k4t8s+wM+3zUAsGo+AXuRLahdYwP2SycQWHTA4vcAAPK7b8HUKAgDgGiD4c93/+8//UegJQCAZkmScQAAXkQkLlTKsz/HCAAARKCBKrBBG/TBGCzABhzBBdzBC/xgNoRCJMTCQhBCCmSAHHJgKayCQiiGzbAdKmAv1EAdNMBRaIaTcA4uwlW4Dj1wD/phCJ7BKLyBCQRByAgTYSHaiAFiilgjjggXmYX4IcFIBBKLJCDJiBRRIkuRNUgxUopUIFVIHfI9cgI5h1xGupE7yAAygvyGvEcxlIGyUT3UDLVDuag3GoRGogvQZHQxmo8WoJvQcrQaPYw2oefQq2gP2o8+Q8cwwOgYBzPEbDAuxsNCsTgsCZNjy7EirAyrxhqwVqwDu4n1Y8+xdwQSgUXACTYEd0IgYR5BSFhMWE7YSKggHCQ0EdoJNwkDhFHCJyKTqEu0JroR+cQYYjIxh1hILCPWEo8TLxB7iEPENyQSiUMyJ7mQAkmxpFTSEtJG0m5SI+ksqZs0SBojk8naZGuyBzmULCAryIXkneTD5DPkG+Qh8lsKnWJAcaT4U+IoUspqShnlEOU05QZlmDJBVaOaUt2ooVQRNY9aQq2htlKvUYeoEzR1mjnNgxZJS6WtopXTGmgXaPdpr+h0uhHdlR5Ol9BX0svpR+iX6AP0dwwNhhWDx4hnKBmbGAcYZxl3GK+YTKYZ04sZx1QwNzHrmOeZD5lvVVgqtip8FZHKCpVKlSaVGyovVKmqpqreqgtV81XLVI+pXlN9rkZVM1PjqQnUlqtVqp1Q61MbU2epO6iHqmeob1Q/pH5Z/YkGWcNMw09DpFGgsV/jvMYgC2MZs3gsIWsNq4Z1gTXEJrHN2Xx2KruY/R27iz2qqaE5QzNKM1ezUvOUZj8H45hx+Jx0TgnnKKeX836K3hTvKeIpG6Y0TLkxZVxrqpaXllirSKtRq0frvTau7aedpr1Fu1n7gQ5Bx0onXCdHZ4/OBZ3nU9lT3acKpxZNPTr1ri6qa6UbobtEd79up+6Ynr5egJ5Mb6feeb3n+hx9L/1U/W36p/VHDFgGswwkBtsMzhg8xTVxbzwdL8fb8VFDXcNAQ6VhlWGX4YSRudE8o9VGjUYPjGnGXOMk423GbcajJgYmISZLTepN7ppSTbmmKaY7TDtMx83MzaLN1pk1mz0x1zLnm+eb15vft2BaeFostqi2uGVJsuRaplnutrxuhVo5WaVYVVpds0atna0l1rutu6cRp7lOk06rntZnw7Dxtsm2qbcZsOXYBtuutm22fWFnYhdnt8Wuw+6TvZN9un2N/T0HDYfZDqsdWh1+c7RyFDpWOt6azpzuP33F9JbpL2dYzxDP2DPjthPLKcRpnVOb00dnF2e5c4PziIuJS4LLLpc+Lpsbxt3IveRKdPVxXeF60vWdm7Obwu2o26/uNu5p7ofcn8w0nymeWTNz0MPIQ+BR5dE/C5+VMGvfrH5PQ0+BZ7XnIy9jL5FXrdewt6V3qvdh7xc+9j5yn+M+4zw33jLeWV/MN8C3yLfLT8Nvnl+F30N/I/9k/3r/0QCngCUBZwOJgUGBWwL7+Hp8Ib+OPzrbZfay2e1BjKC5QRVBj4KtguXBrSFoyOyQrSH355jOkc5pDoVQfujW0Adh5mGLw34MJ4WHhVeGP45wiFga0TGXNXfR3ENz30T6RJZE3ptnMU85ry1KNSo+qi5qPNo3ujS6P8YuZlnM1VidWElsSxw5LiquNm5svt/87fOH4p3iC+N7F5gvyF1weaHOwvSFpxapLhIsOpZATIhOOJTwQRAqqBaMJfITdyWOCnnCHcJnIi/RNtGI2ENcKh5O8kgqTXqS7JG8NXkkxTOlLOW5hCepkLxMDUzdmzqeFpp2IG0yPTq9MYOSkZBxQqohTZO2Z+pn5mZ2y6xlhbL+xW6Lty8elQfJa7OQrAVZLQq2QqboVFoo1yoHsmdlV2a/zYnKOZarnivN7cyzytuQN5zvn//tEsIS4ZK2pYZLVy0dWOa9rGo5sjxxedsK4xUFK4ZWBqw8uIq2Km3VT6vtV5eufr0mek1rgV7ByoLBtQFr6wtVCuWFfevc1+1dT1gvWd+1YfqGnRs+FYmKrhTbF5cVf9go3HjlG4dvyr+Z3JS0qavEuWTPZtJm6ebeLZ5bDpaql+aXDm4N2dq0Dd9WtO319kXbL5fNKNu7g7ZDuaO/PLi8ZafJzs07P1SkVPRU+lQ27tLdtWHX+G7R7ht7vPY07NXbW7z3/T7JvttVAVVN1WbVZftJ+7P3P66Jqun4lvttXa1ObXHtxwPSA/0HIw6217nU1R3SPVRSj9Yr60cOxx++/p3vdy0NNg1VjZzG4iNwRHnk6fcJ3/ceDTradox7rOEH0x92HWcdL2pCmvKaRptTmvtbYlu6T8w+0dbq3nr8R9sfD5w0PFl5SvNUyWna6YLTk2fyz4ydlZ19fi753GDborZ752PO32oPb++6EHTh0kX/i+c7vDvOXPK4dPKy2+UTV7hXmq86X23qdOo8/pPTT8e7nLuarrlca7nuer21e2b36RueN87d9L158Rb/1tWeOT3dvfN6b/fF9/XfFt1+cif9zsu72Xcn7q28T7xf9EDtQdlD3YfVP1v+3Njv3H9qwHeg89HcR/cGhYPP/pH1jw9DBY+Zj8uGDYbrnjg+OTniP3L96fynQ89kzyaeF/6i/suuFxYvfvjV69fO0ZjRoZfyl5O/bXyl/erA6xmv28bCxh6+yXgzMV70VvvtwXfcdx3vo98PT+R8IH8o/2j5sfVT0Kf7kxmTk/8EA5jz/GMzLdsAAAAgY0hSTQAAeiUAAICDAAD5/wAAgOkAAHUwAADqYAAAOpgAABdvkl/FRgAADdJJREFUeNqMWVuMZNdVXfucc++tR79f43l6HvF4bOfhF7ZjJ2BQbAK2Q1Ck/EAi4ggREBglQpGi8PogID6QgD8kRL4MEYn9A3LiIE+IhWUn8dvjsT3TmZ4ZT8/0dE9Pd3VV3cc5Z+/NR1X1VLd7EFc6fW+rqu9dd+29z157Ndkn5zF00NB5+NoMnc3Q5yQKo6L6gb8jKAAYQyBAAGh/yXXOGPrO4BpuGzjaAegAlB1cswLogTKN1CS3jWfNmqVMQSJAqKKYkjW2AvulgmMUFRDUEGkfrPTvLTsAGz7UbQNHO/w+AGdZFBDV8ZpL757OZh6cq8/sb7rJuZrNBOCuj1mrCONZLV3Io/p1z8VCJ3bnO6F7aiOUl4roWZSMIaKtz5PtwAafkX1y/nrhHCyrgJEomKzZ9LF9zf2P7Gse3Fd34yWr6UTxXVZfBDHfe+Htr751buUjv3nfzf9y5NCep6rARoEgqr4dpJxvh/y1Nd852wlVVLDtpQH31/YU0GEGt7O2CY5FDRT0yP7m3O8cGbtlfyOZa0fRpZJjEaUqWaVScLf0Y68tLN26dHmt8d6FyY9N7t71vbaPLICKAqxwszVb/8W5mjnYdOWJdZ8vlRwMoERbwJlhRt0O4dwsCBalzJD5w2MTRz5/oHlrIVq7XMZQsEoRVQoRLVjVC9D1Iobg4QhBqVrzjLYXRFWNAnhRRFFlKDmD5JbxpD5Ts/Z0O5SeFYY2QW0B6a6XdyxK05m13/jw5NEHd9VvXffiNgKHnFWLqCgEMShCwZBuVORREK1TpBkqMmgFoW4UUYXkrFXOAlaQZ6VuFI0KWMAeGnHpYs6+EwSGNqM5KKItRbKZe6xq6s7Q12+bPPzgrvota17sRpDYjardqBwUVVGFmdNLax/vBJapmanvV6yqjREgWlRJDeteA5fVR8vWxmfrjfrJRlZ7ZjHouY4X6xW2YOE8CjsytLdhk/dFUfSY1GGy3PZ9TgEDAb58dHTPp26o37LuJdkIEtpBkLP6yGrPXO382vEzq4+cuNLdpUR41NXz0Wb2AiamgTQiNkbBIric85dfXpG7amn18E2T5nMTzfTbXeA7ayWzV7UCcKViFnPorpp15/OoOhTSAYNbQius9Kt7m2O/dWjslk6UrB3Fd6OgiFIWLFP/s9J5/IeL7Xu67IAbprC7kZaSuliwkpmdIHgFjSXY8BGNica7B0Yaty16qb0VdP+Y0p9/aCq9s7hS/OWlrl+x1iRE0E4UrTtgf8MlZ7vRW4IZbDVuW96ZqZq1Xzw0cgTQ8XZQ342KPGjIRaf+M/df+1HQo9g9ij31JNyZ2OdGgz7bLvhMoZi0e0YABYhA7aVOUnr/z3ubyXMHdtc/c6bmHrkYJHmD6NGbZrJpnm89sdzyK9aSswRdKUUmR42dzkyyWskmSLelegX6yL7m9JHRZE8rSMxZuIgiHpo826A/+FHijmImxe3GXLqnxf/UXg8vbwRBHgUutWr21wBrYDsB+SJ0LQiW8+Jte6V848CBkeP1m8f+5OeODpwmfPzobPLX8fnlP1orYmUMGSLYpZLlyEji1ryPg2LZsqVM1a379A31fRWry1lCwSohSvX6hPvM8Znko9jbwO0ztQv3rsdvtVarn7SCJIWoq1iFCewmEmDawTUsPCsHUfWKdD1q9tqp1o/o1dU/PpjQAjcdzs7WH5q7fepLCSgAMAYwG0FRitJsZh33Gh9d6xoK3DOdje5rJlPtKL6Iyj5IeaVmD/5gKnssZikOJ2n7nvPl319d9fMdReZV2bPGSpRZVFIyABxSYzSqSskqlYBFVWGp8fP3u6eTV9b+YjdMuwBh4/Do783ubRzjqHFQqJdL1rmaGfR9MpvbDAG3T2WTCnUFayyicsUaX5lMH7robL1uHe5Yrp7qLFdvFkDiRaNnxEo0VqyBVdkSEfUbdyUaK9EoqgpACQAlprEw3/rZxMLGt5sArhBN1I6Nfz61pKogQ7AtLyCQaTgyOmCQFRhLrT0ykowVUbnsPdSvp2bq7ZHkXoBwKMql5oXu99uitpIe+JJlADBGQSAi7b+tBgGzqAz3VgIQQdnVd1pPT7MuBgD5XO3T45PpnIoq9bBQzoqJxFjRQYhVabZmk+nM1rpRfBmVQ5Byqe5uumjNjAOwdz280G3HlVIVFWssewwFzxpK0RBFebMlEUSgvL3xA1DrKFlbrZbc5eJ4AiC35kByQ+Njyr0wE0DrgdETPDoACB1xlGYWtssaS9ZYAnKp6Y4WAJoAmqvlq10WqVi5FGXP4IqVK1H2ouwVUQcilaCmp1BkaG2CDKJWV4qf1gB4AEViPkTAoHIpMsA9QjcFK1mCjQLtARDJRWk5MbsFQA3Iq05Yylm1BGIlKp6V+2AljxqHGezfclidbFXsRCZfLt93QFEB9UgYp/7GTAQKqgBDqb9RD6qEoiBWrFJGlYIVvv8CCZCXQboFq1S9AugxycqFiFSiHBQ8pN22h5aGZTwRqAhSJkAXQF23vgRYe7ME0ZDkV0C99kIWekxCtCd5GDClAhVrrABbiErZAyhBIZ6VFSA2lPZjnIG2gMTWFgsFYKRX8B84LAGOCKp6DTmrimcNlWgsenlYWdYWASiAEU+oVb2C6DHHwmUvzEIEc6Ubrk6sVy8dA1obS/kLGyWzMUTbi6QPT+ojbjQCIwqAVKtN5NoDl9relrDJYBRwIeo9KwpWLYOUjY3qHRq1j+ZAGqfSQ9WF/PWCelKpZIioCgEgQ7RRcXX6+KU/HWu46YV1vxgNZXRN122dN1SjzNZvrlgTAmCiLvVzVRXQ1ABNR4CqOgAKguYssRvEe1HyouhGEbNUvj6aOt8CpeuJeyAQnsqjRC9QUZWteUW0nsd8rRvbxlBC9IEhaMCQppmlGOwvhQWPhqI0K/4ttZRQD7xO16xJewT2ABIRlksOlwquiOC6UbSrStwKJ6dP5ydbAbe3HD0w2kiPlVeLE0rIdsodY8jiWl7tNEYCQJlm7iPVpep+xBKO9OViozhlLFkAAoUcbLj0bDcGAGoAqCFoN4gsl7ECwKUglgxeL7k1vrrx3Wz+fbROnm9oq/W7tcSQgGSHBxP+70MVxIklo6vLXylPn667M6cgV1a+GxQFAIhCGonBVGbN+W6MxlwThgpAT7R8qQAXUWPOGjei2HbU/9jdWnxD59/EyonXHx5fff9xa03eB6k7gKQd5myASKyzRXrxzOP5e29+Ss+8jfTK4kveuB+oIgGgqso3jSVJJ4rkQSINGOyHWd9thXLDS/Qi3AkSyih6KdqrZmzyb6bXLhTVwrtYf/n5r86dfePxWmJLts7/fxhUm3hLVGbv/PRL5as//posLiC5fK6t0zd8KyS1LvXatADAPdO17MS6L/t3U2s+94Qd7OCeFc4STWfGLnRibEfVPHLSqk2c2eViO55+65c7a1dNvLjwyZlyfS6bmHy3akysCBntdc0ea0pG1ViGdcFaW9ZWF/cmP3nm6+XbP/v9mHeM665Hd8td3/RHPvZfJDEDwMzq75zJst11Z567lG9Y0+tE1nzuCXPt7YmulMxHx9L0/TzyaiVqCCRQV83sf2VP3bT17DsPtNdbtn3x3Iez8+98erxzZSpNXGlUqsSSd86FGnuTFRtjzfWLN9deOf7b4cVnv9m9sHCfVCVsKIvk9k/+WfyFh/4VIhmgIgoeSYx+8dDYxNPnO1dbQaIhEgBC9sl5N2wOscDeOOLSgyMu+/FSGY2BI8AKyCRp4vctvPbr8aVnv3HxwuLhyAIyBrUsCdno+AXbHFsx9UaHfDnK7fXZfKO1r6y8UwWMCpLJmZN078N/FT76wH9DOIOIKMASxX/l2MT0csnF02fbq9aZgSUiZJ+ct0OOghnYHXdP1+oC2FdXSzaGHAFOAaIkrWbz1f2jJ174Que9Nz97deXKvipyb4sVudZ6iQAySC0hGxs/h8O3/nu461eeDNN7luHLGlRZAZYg/rGDI+NHx1L7DyfXLgpIia4poQHAYdujNxsrzP2ztUbOal5dLZmIrKG+y2UsJ8bwVGdlf335/H10/tS93atXj4TgJwFYIiNZmlytTUzOd3cffrGYu/HFYvKGS6LiiNkAYFGwRvGfPTQ6ddt4mv7d22vnS1WxRMM6Usg+Ob/dnByAJFU198/W66mh5MWVIpSsZA0NUoLYWHHWBschUeF6vzOBQCCiCGOKYJMgIqnhOOjLzKwxdaRfOjy2a1fd0t+eWDtXCaI1mwbSjgBpByZJRM0d01n9cDNJX1+r+OftwACMNXTNjSBC3+/Tod5G/R+blhqzRij47pnayBeOjO5e6ITWP77XuiC9eWbY4bo2Jgz5g7SD3Uvadxt2NVzyiblaMyFyr65V/tSGj30/ysDA2N68tEVSsUIh2vP/CLhjKmv+xr7m3FRqzb+da1948XK5RpYGfozupL4HAK/XBa7NzQoDVTo6nmb3z9RGRhOTnO9EOdsN8VLJfrmIcVv3kNmatQcarnFsPG18fLY2FgXyw6V8+ZnF7jIYYtymfy07yLJNgLiOBbczUOlNkDeOJOnRsaT5idnaqCWqXyyYgiiLqliCcUTJgaZzU5mNzy8X7XdbofXyatmCQIwjog+a6Dst0JDLfz2H/wNhB0AsOjDKKLHkes/cqu+jqoZ+3gGAtZsC9nrgPuD0ux2M62GJvl2yD4Ygsj23cfCvCPGqtIMRjn7L2g5Ats0uuN75fwcA5pFRO96OufAAAAAASUVORK5CYII=";
    
    unsigned char *decodeData;
    int dataSize = base64Decode((unsigned char*)data, strlen(data), &decodeData);
    showImageUsingData(decodeData, dataSize);
}



void ResourceTest::testTexturePacker()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texturePacker/data.plist","texturePacker/data.pvr.ccz");
    
//    sean: why create a spriteBatchNode?
//    
    auto *texture = Director::getInstance()->getTextureCache()->getTextureForKey("texturePacker/data.pvr.ccz");
    auto *node= SpriteBatchNode::createWithTexture(texture);
    addChild(node);
    
    //    sean: Test parent node different
    //    seem no different.
    //
//    for (int i = 0; i < 10000; i++) {
//        auto sprite = Sprite::createWithSpriteFrameName("HelloWorld.png");
//        Size visibleSize = Director::getInstance()->getVisibleSize();
//        int x = rand()%(int)visibleSize.width;
//        int y = rand()%(int)visibleSize.height;
//
//        sprite->setPosition(Point(x, y));
//        
////        node->addChild(sprite);         // 0.4s on mac
//        this->addChild(sprite);           // 0.4s on mac
//
//    }
    
    auto *s1 = Sprite::createWithSpriteFrameName("HelloWorld.png");
    
    s1->setPosition(Point(355,325));
    s1->setAnchorPoint(Point::ZERO);

    node->addChild(s1);

    auto *s2 = Sprite::createWithSpriteFrameName("CloseNormal.png");

    s2->setPosition(Point(100,100));
    s2->setAnchorPoint(Point::ZERO);

    node->addChild(s2);

}

