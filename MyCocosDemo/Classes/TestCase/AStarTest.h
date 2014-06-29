//
//  AStarTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 06/29/14
//
//

#ifndef __MyCocosDemo__AStarTest__
#define __MyCocosDemo__AStarTest__

#include "BaseTestScene.h"

class GridLayer;
class Step;

class AStarTest : public BaseTestScene
{
public:
    AStarTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    void testAStar();

private:
    void initScene();
    void infoMap();
    
private:
    // UI
    GridLayer* m_gridLayer;
    
    // Data
    // Screen Size is 1280, 768, Grid Size = 100
//    int mapData[7][12];
    int **m_mapData;
    int m_row;
    int m_col;
};


class GridLayer : public Layer
{
public:
    GridLayer();
    virtual ~GridLayer();
    virtual bool init() override;
    
    CREATE_FUNC(GridLayer);
    
    virtual void draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated) override;
    void drawGrid(int row, int col);
    void AStar();
    void setMapData(int** mapData, int row, int col);

private:
    int **m_data;
    int m_row;
    int m_col;
    
    std::vector<Step*> openList;
    std::vector<Step*> closedList;

};

class Step
{
public:
    Step();
    Step(int gx, int gy, int h, Step* parent);
    virtual ~Step();
    
public:
    int f;      // f = g + h
    int g;      // 每格的移动量
    int h;      // 移动估算值
    
    int dir;
    int gx;
    int gy;
    
    Step* parent;   // 父节点
};

#endif /* defined(__MyCocosDemo__AStarTest__) */