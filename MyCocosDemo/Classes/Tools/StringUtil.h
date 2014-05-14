//
//  StringUtil.h
//  MyCocosDemo
//
//  Created by shihongyang on 5/15/14.
//
//

#ifndef __MyCocosDemo__StringUtil__
#define __MyCocosDemo__StringUtil__

#include <iostream>
#include <vector>

class StringUtil
{
public:
    static std::vector<std::string>& split(const std::string& source, char delim, std::vector<std::string>& tokens);
    static int intValue(const char *text, int defaultValue);

};
#endif /* defined(__MyCocosDemo__StringUtil__) */
