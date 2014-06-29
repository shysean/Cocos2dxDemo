//
//  AStarTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 06/29/14.
//
//

#include "AStarTest.h"
#include "../Tools/GLDrawer.h"

#define GRID_ROW 7
#define GRID_COL 12

AStarTest::AStarTest()
: m_gridLayer(nullptr)
, m_mapData(nullptr)
, m_row(GRID_ROW)
, m_col(GRID_COL)
{

    m_mapData = new int*[m_row];
    
    for(int i = 0; i < m_row; i++)
    {
        m_mapData[i] = new int[m_col];
    }
    
    for (int row = 0; row < m_row; row++)
    {
        for (int col = 0; col < m_col; col++)
        {
            m_mapData[row][col] = -1;
        }
    }

    
    infoMap();
}

void AStarTest::infoMap()
{
//    Mock Data:
//    int mapData[7][12] = {
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
    for (int row = 0; row < m_row; row++)
    {
        for (int col = 0; col < m_col; col++)
        {
            char c_num[10];
            sprintf(c_num, "%d", m_mapData[row][col]);
            info.append("\t");
            info.append(c_num);
        }
        info.append("\n");
    }
    
    CCLOG("%s", info.c_str());
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
    
    m_gridLayer->setMapData(m_mapData, m_row, m_col);
}

// =============================
//        GridLyaer
// =============================
GridLayer::GridLayer()
: m_data(nullptr)
{
    
}
GridLayer::~GridLayer()
{
    
}
bool GridLayer::init()
{
    return true;
}
void GridLayer::draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    if (m_data == nullptr) {
        return;
    }
    
    for (int r = 0; r < m_row; r++) {
        for (int c = 0; c < m_col; c++) {
            drawGrid(r, c);
        }
    }
    
}
void GridLayer::setMapData(int** mapData, int row, int col)
{
    m_data = mapData;
    m_row = row;
    m_col = col;
}
void GridLayer::drawGrid(int row, int col)
{
    int offsetX = 40;
    int offsetY = 34;
    
    int gridSize = 100;
    
    int startX = offsetX + col * gridSize;
    int startY = offsetY + row * gridSize;
    int endX = startX + gridSize;
    int endY = startY + gridSize;
    
    GLDrawer::drawRect(startX, startY, endX, endY, Color4B::BLUE);
}

void GridLayer::AStar()
{
    Point start(3,3);
    Point end(8,8);
    
    
    // #1
    Step* selectStep = new Step(3, 3, 10, nullptr);
    openList.push_back(selectStep);
    
    // #2
    
}

// =============================
//        Step
// =============================
Step::Step()
{
    
}
Step::~Step()
{
    
}
Step::Step(int gx, int gy, int h, Step* parent)
{
    this->h = h;
    this->parent = parent;
    this->g = 1;
    this->f = this->h + this->g;
    this->gx = gx;
    this->gy = gy;
}

// =============================
//        Test Funtion
// =============================
void AStarTest::testAStar()
{
    setInfo("testAStar");
    
    m_gridLayer->AStar();
    
}