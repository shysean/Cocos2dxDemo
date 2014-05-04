//
//  GameText.h
//  MyCocosDemo
//
//  Created by shihongyang on 4/30/14.
//
//

#ifndef __MyCocosDemo__GameText__
#define __MyCocosDemo__GameText__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

typedef std::unordered_map<std::string, std::string> StringMap;

class GameText
{
private:
    
    GameText();
    ~GameText();
    
    bool init();
    
public:
    static GameText* getInstance();
    string getText(string key);
    

    
private:
    
    static GameText* m_instance;
    
    static bool m_isReady;
    StringMap m_stringMap;


};

#endif /* defined(__MyCocosDemo__GameText__) */
