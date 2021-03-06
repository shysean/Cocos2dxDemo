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
    
private:
    GridLayer* m_gridLayer;

};


class GridLayer : public Layer
{
public:
    GridLayer();
    virtual ~GridLayer();
    virtual bool init() override;
    
    CREATE_FUNC(GridLayer);
    
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    
    void drawGrid(int row, int col, Color4B color);

    void testAstar();
    void clear();
    
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    
private:

    void setPoint(int x, int y, int value);
    void infoMap();

private:
    int **m_data;
    int m_row;
    int m_col;

    
    bool m_isDragStartPoint;
    bool m_isDragEndPoint;
};



#endif /* defined(__MyCocosDemo__AStarTest__) */