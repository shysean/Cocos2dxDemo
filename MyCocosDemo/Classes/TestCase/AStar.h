//
//  AStar.h
//  MyCocosDemo
//
//  Created by shihongyang on 6/30/14.
//
//

#ifndef __MyCocosDemo__AStar__
#define __MyCocosDemo__AStar__

#include "cocos2d.h"
class Step
{
public:
    Step(){};
    ~Step(){};
    Step(int gx, int gy,int g, int h, Step* parent);
    
public:
    int f;      // f = g + h
    int g;      // 移动量
    int h;      // 移动估算值
    
    int dir;
    int gx;
    int gy;
    
    Step* parent;   // 父节点
};

class AStar
{
    
public:
    std::vector<Step*> getPath(int sx, int sy, int ex, int ey);

    AStar();
    AStar(int** mapData, int row, int col);
    virtual ~AStar(){};
    
private:
    Step *createStep(int gX, int gY, Step* parent);
    bool checkStep(Step* step);
    Step *searchBestStep();
    void searchAroundStep(Step* step);
    Step *rollbackParentStep();
    
private:
    std::vector<Step*> m_openList;
    std::vector<Step*> m_closedList;
    int m_row;
    int m_col;
    int m_startX;
    int m_startY;
    int m_endX;
    int m_endY;
    int** m_data;
};


#endif /* defined(__MyCocosDemo__AStar__) */
