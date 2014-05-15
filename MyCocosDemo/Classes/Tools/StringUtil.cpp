//
//  StringUtil.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 5/15/14.
//
//

#include "StringUtil.h"

std::vector<std::string>& StringUtil::split(const std::string& source, char delim, std::vector<std::string>& tokens)
{
    std::stringstream ss(source);
    std::string item;
    
    while (std::getline(ss, item, delim))
        tokens.push_back(item);
    
    return tokens;
}

int StringUtil::intValue(const char *text, int defaultValue)
{
	if(text == NULL) {
		return defaultValue;
	}
	
	return std::atoi(text);
}