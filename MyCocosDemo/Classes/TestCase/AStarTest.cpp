//
//  AStarTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 06/29/14.
//
//

#include "AStarTest.h"
#include "AStar.h"
#include "../Tools/GLDrawer.h"

#define GRID_ROW 7
#define GRID_COL 12

AStarTest::AStarTest()
: m_gridLayer(nullptr)
{

}

void AStarTest::runThisTest()
{
    initScene();
    Director::getInstance()->replaceScene(this);
}

void AStarTest::initTestMenu()
{
    ADD_TEST_METHOD(testAStar);
}

void AStarTest::initScene()
{
    m_gridLayer = GridLayer::create();
    this->addChild(m_gridLayer);
}

// =============================
//        GridLyaer
// =============================
GridLayer::GridLayer()
: m_data(nullptr)
, m_row(GRID_ROW)
, m_col(GRID_COL)
{
    
}
GridLayer::~GridLayer()
{
    
}
bool GridLayer::init()
{
    
    // 初始化数组
    m_data = new int*[m_row];
    
    for(int i = 0; i < m_row; i++)
    {
        m_data[i] = new int[m_col];
    }
    
    for (int row = 0; row < m_row; row++)
    {
        for (int col = 0; col < m_col; col++)
        {
            m_data[row][col] = 0;
        }
    }
    
//    m_data[0][1] = 10;    // (1,0) = 10;
    
    infoMap();
    // 注册监听事件
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
//    bool(Touch*, Event*)

    touchListener->onTouchBegan = CC_CALLBACK_2(GridLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GridLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GridLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

bool GridLayer::onTouchBegan(Touch* touch, Event* event)
{
    Point p = touch->getLocation();
    CCLOG("onTouchBegan %f %f", p.x, p.y);
    int x = (int)p.x;
    int y = (int)p.y;
    
    int offsetX = 40;
    int offsetY = 34;
    
    int gridSize = 100;
    
    int gx = (x - offsetX) / gridSize;
    int gy = (y - offsetY) / gridSize;
    
    if (m_data[gy][gx] == -1) {
        m_data[gy][gx] = 0;
    }
    else
    {
        m_data[gy][gx] = -1;
    }
    
    infoMap();

    return true;
}
void GridLayer::onTouchMoved(Touch* touch, Event* event)
{
//    CCLOG("onTouchMoved");
}
void GridLayer::onTouchEnded(Touch* touch, Event* event)
{
    CCLOG("onTouchEnded");
}
void GridLayer::draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    if (m_data == nullptr) {
        return;
    }
    
    for (int r = 0; r < m_row; r++) {
        for (int c = 0; c < m_col; c++) {
            if (m_data[r][c] == 0)
            {
                drawGrid(r, c, Color4B::BLUE);
            }
        }
    }
    
    for (int r = 0; r < m_row; r++) {
        for (int c = 0; c < m_col; c++) {
            if(m_data[r][c] == -1)
            {
                drawGrid(r, c, Color4B::RED);
            }
        }
    }
    
    
    for (int r = 0; r < m_row; r++) {
        for (int c = 0; c < m_col; c++) {
            if(m_data[r][c] == 1)
            {
                drawGrid(r, c, Color4B::GREEN);
            }
        }
    }
    
}

void GridLayer::drawGrid(int row, int col, Color4B color)
{
    int offsetX = 40;
    int offsetY = 34;
    
    int gridSize = 100;
    
    int startX = offsetX + col * gridSize;
    int startY = offsetY + row * gridSize;
    int endX = startX + gridSize;
    int endY = startY + gridSize;
    
    GLDrawer::drawRect(startX, startY, endX, endY, color);
}


void GridLayer::infoMap()
{
//    Mock Data:
//    int m_mapData[7][12] = {
//        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
//        {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 110, 111},
//        {20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 210, 211},
//        {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 310, 311},
//        {40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 410, 411},
//        {50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 510, 511},
//        {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 610, 611},
//    };
    std::string info;
    
    info.append("\n");
    
//    for (int row = 0; row < m_row; row++)
    for (int row = m_row - 1; row >= 0; row--)
    {
        for (int col = 0; col < m_col; col++)
        {
            char c_num[10];
            sprintf(c_num, "%d", m_data[row][col]);
            info.append("\t");
            info.append(c_num);
        }
        info.append("\n");
    }
    
    CCLOG("%s", info.c_str());
}

void GridLayer::testAstar()
{
    for (int r = 0; r < m_row; r++) {
        for (int c = 0; c < m_col; c++) {
            if(m_data[r][c] == 1)
            {
                m_data[r][c] = 0;
            }
        }
    }
    
    AStar* astar = new AStar(m_data, m_row, m_col);
    std::vector<Step*> moveList = astar->getPath(1, 1, 5, 6);
    delete astar;
    
    for (auto step : moveList)
    {
        m_data[step->gy][step->gx] = 1;
    }
    
    infoMap();
}


// =============================
//        Test Funtion
// =============================
void AStarTest::testAStar()
{
    setInfo("testAStar");
    
    m_gridLayer->testAstar();
    
}