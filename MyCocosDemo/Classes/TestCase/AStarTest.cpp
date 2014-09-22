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

namespace {
    static int FLAG_EMPTY = 0;
    static int FLAG_START = 10;
    static int FLAG_END = 11;
    static int FLAG_PATH = 1;
    static int FLAG_BLOCK = -1;
}

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
, m_isDragStartPoint(false)
, m_isDragEndPoint(false)
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
            m_data[row][col] = FLAG_EMPTY;
        }
    }

    setPoint(1, 1, FLAG_START);
    setPoint(10, 1, FLAG_END);
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

void GridLayer::setPoint(int x, int y, int value)
{
    if (m_data == nullptr) {
        return;
    }
    
    m_data[y][x] = value;
}


bool GridLayer::onTouchBegan(Touch* touch, Event* event)
{
    Point p = touch->getLocation();
    //    CCLOG("onTouchBegan %f %f", p.x, p.y);
    int x = (int)p.x;
    int y = (int)p.y;
    
    int offsetX = 40;
    int offsetY = 34;
    
    int gridSize = 100;
    
    int gx = (x - offsetX) / gridSize;
    int gy = (y - offsetY) / gridSize;
    
    if (m_data[gy][gx] == FLAG_START){
        m_isDragStartPoint = true;
    }
    
    if (m_data[gy][gx] == FLAG_END) {
        m_isDragEndPoint = true;
    }
    
    return true;
}
void GridLayer::onTouchMoved(Touch* touch, Event* event)
{
//    CCLOG("onTouchMoved");
    
    for (int r = 0; r < m_row; r++) {
        for (int c = 0; c < m_col; c++) {
            if (m_isDragStartPoint && m_data[r][c] == FLAG_START) {
                m_data[r][c] = FLAG_EMPTY;
            }
            
            if (m_isDragEndPoint && m_data[r][c] == FLAG_END) {
                m_data[r][c] = FLAG_EMPTY;
            }
        }
    }
    
    Point p = touch->getLocation();
    //    CCLOG("onTouchBegan %f %f", p.x, p.y);
    int x = (int)p.x;
    int y = (int)p.y;
    
    int offsetX = 40;
    int offsetY = 34;
    
    int gridSize = 100;
    
    int gx = (x - offsetX) / gridSize;
    int gy = (y - offsetY) / gridSize;
    
    if (m_isDragStartPoint) {
        setPoint(gx, gy, FLAG_START);
    }
    
    if (m_isDragEndPoint) {
        setPoint(gx, gy, FLAG_END);
    }

}
void GridLayer::onTouchEnded(Touch* touch, Event* event)
{
    CCLOG("onTouchEnded");
    if (m_isDragEndPoint)
    {
        m_isDragEndPoint = false;
        return;
    }
    if (m_isDragStartPoint) {
        m_isDragStartPoint = false;
        return;
    }

    Point p = touch->getLocation();
//    CCLOG("onTouchBegan %f %f", p.x, p.y);
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
    
}

void GridLayer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    if (m_data == nullptr) {
        return;
    }
    
    for (int r = 0; r < m_row; r++) {
        for (int c = 0; c < m_col; c++) {
            if (m_data[r][c] == FLAG_EMPTY)
            {
                drawGrid(r, c, Color4B::BLUE);
            }
        }
    }
    
    for (int r = 0; r < m_row; r++) {
        for (int c = 0; c < m_col; c++) {
            if(m_data[r][c] == FLAG_BLOCK)
            {
                drawGrid(r, c, Color4B::RED);
            }
        }
    }
    
    
    for (int r = 0; r < m_row; r++) {
        for (int c = 0; c < m_col; c++) {
            if(m_data[r][c] == FLAG_PATH)
            {
                drawGrid(r, c, Color4B::GREEN);
            }
        }
    }
    
    for (int r = 0; r < m_row; r++) {
        for (int c = 0; c < m_col; c++) {
            if(m_data[r][c] == FLAG_END || m_data[r][c] == FLAG_START)
            {
                drawGrid(r, c, Color4B::YELLOW);
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
    int startX;
    int startY;
    int endX;
    int endY;
    
    for (int r = 0; r < m_row; r++) {
        for (int c = 0; c < m_col; c++) {
            if(m_data[r][c] == FLAG_PATH)
            {
                m_data[r][c] = FLAG_EMPTY;
            }
            
            if (m_data[r][c] == FLAG_START)
            {
                startX = c;
                startY = r;
            }
            
            if (m_data[r][c] == FLAG_END)
            {
                endX = c;
                endY = r;
            }
        }
    }
    
    AStar* astar = new AStar(m_data, m_row, m_col);
    std::vector<Step*> moveList = astar->getPath(startX, startY, endX, endY);
    delete astar;
    
    // 删除起点终点
    moveList.pop_back();
    std::vector<Step*>::iterator iter = moveList.begin();
    moveList.erase(iter);
    
    // 赋值
    for (auto step : moveList)
    {
        m_data[step->gy][step->gx] = 1;
    }
    

    
    infoMap();
}

void GridLayer::clear()
{
    
}

// =============================
//        Test Funtion
// =============================
void AStarTest::testAStar()
{
    setInfo("testAStar");
    
    m_gridLayer->testAstar();
    
}