//
//  AStar.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 6/30/14.
//
//

#include "AStar.h"

// =============================
//        Step
// =============================
Step::Step(int gx, int gy, int g, int h, Step* parent)
{
    this->parent = parent;
    
    this->h = h;
    this->g = g;
    this->f = this->h + this->g;
    
    this->gx = gx;
    this->gy = gy;
}

// =============================
//          A*
// =============================
AStar::AStar()
: m_data(nullptr)
, m_col(0)
, m_row(0)
, m_endX(0)
, m_endY(0)
, m_startX(0)
, m_startY(0)
{
}
AStar::AStar(int** mapData, int row, int col)
: m_endX(0)
, m_endY(0)
, m_startX(0)
, m_startY(0)
{
    m_data = mapData;
    m_row = row;
    m_col = col;
}

std::vector<Step*> AStar::getPath(int sx, int sy, int ex, int ey)
{
    m_startX = sx;
    m_startY = sy;
    m_endX = ex;
    m_endY = ey;
    
    Step* selectStep = createStep(m_startX, m_startY, nullptr);
    m_openList.push_back(selectStep);
    
    do{
        selectStep = searchBestStep();
//        CCLOG("selectStep(%d,%d) g=%d h=%d f=%d", selectStep->gx, selectStep->gy, selectStep->g, selectStep->h, selectStep->f);
//        m_data[selectStep->gy][selectStep->gx] = 0;
        
        searchAroundStep(selectStep);
    }while (selectStep->gx != m_endX || selectStep->gy != m_endY);
    
    
    CCLOG("m_openListSize=%lu, m_closedListSize=%lu", m_openList.size(), m_closedList.size());
    CCLOG("selectStep(%d,%d) g=%d h=%d f=%d", selectStep->gx, selectStep->gy, selectStep->g, selectStep->h, selectStep->f);

    
    
    std::vector<Step*> result;
    
    int size = m_closedList.size();
    Step* lastStep = m_closedList[size - 1];
    result.push_back(lastStep);
    
    Step* parentStep = lastStep->parent;
    while (parentStep != nullptr) {
        result.push_back(parentStep);
        parentStep = parentStep->parent;
    }
    return result;
}



Step* AStar::createStep(int gX, int gY, Step* parent)
{
    int h = abs(m_endX - gX) + abs(m_endY - gY);
    int g = abs(gX - m_startX) + abs(gY - m_startY);
    Step* selectStep = new Step(gX, gY, g, h, parent);
    return selectStep;
}

bool AStar::checkStep(Step* step)
{
    for (auto s : m_closedList) {
        if (s->gx == step->gx && s->gy == step->gy) {
            return false;
        }
    }
    CCLOG("m_data[2][1]=%d", m_data[2][1]);
    if (m_data[step->gy][step->gx] < 0) {
        return false;
    }
    return true;
}

Step* AStar::searchBestStep()
{
    Step* bestStep;
    
    int minF = 0;
    
    std::vector<Step*> minFStep;
    
    for (std::vector<Step*>::iterator iter = m_openList.begin();iter != m_openList.end(); ++iter)
    {
        Step* step = *iter;
        if (minF == 0 || minF > step->f)
        {
            minF = step->f;
            minFStep.clear();
            minFStep.push_back(step);
            continue;
        }
        
        if (minF == step->f) {
            minFStep.push_back(step);
            continue;
        }
    }
    
    int maxG = 0;
    for (auto s : minFStep){
        CCLOG("step(%d,%d) g=%d f=%d", s->gx, s->gy, s->g, s->f);
        if (maxG == 0 || maxG < s->g)
        {
            maxG = s->g;
            bestStep = s;
        }
    }
    
    // 从m_openList中清理选中的节点
    for (std::vector<Step*>::iterator iter = m_openList.begin();iter != m_openList.end(); ++iter)
    {
        Step* step = *iter;
        if (step == bestStep) {
            iter = m_openList.erase(iter);
            break;
        }
    }
    
    // 放入m_closedList
    m_closedList.push_back(bestStep);
    
    return bestStep;
}

// 四方向
void AStar::searchAroundStep(Step* step)
{
    
    int x = 0;
    int y = 0;
    // 查找selectStep周边节点
    // 左
    x = step->gx - 1;
    y = step->gy;
    
    if (x >= 0 && x < m_col && y >= 0 && y < m_row) {
        Step* leftStep = createStep(x, y, step);
        if (checkStep(leftStep)) {
            m_openList.push_back(leftStep);
        }
    }

    // 右
    x = step->gx + 1;
    y = step->gy;
    if (x >= 0 && x < m_col && y >= 0 && y < m_row) {
        Step* rightStep = createStep(x, y, step);
        if (checkStep(rightStep)) {
            m_openList.push_back(rightStep);
        }
    }
    
    // 上
    x = step->gx;
    y = step->gy + 1;
    if (x >= 0 && x < m_col && y >= 0 && y < m_row) {
        Step* upStep = createStep(x, y, step);
        if (checkStep(upStep)) {
            m_openList.push_back(upStep);
        }
    }
    
    // 下
    x = step->gx;
    y = step->gy - 1;
    if (x >= 0 && x < m_col && y >= 0 && y < m_row) {
        Step* downStep = createStep(x, y, step);
        if (checkStep(downStep)) {
            m_openList.push_back(downStep);
        }
    }
}
