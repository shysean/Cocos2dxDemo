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
        CCLOG("selectStep(%d,%d) g=%d h=%d f=%d", selectStep->gx, selectStep->gy, selectStep->g, selectStep->h, selectStep->f);
        m_data[selectStep->gx][selectStep->gy] = 0;
        
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
    
    if (step->gx < 0 || step->gx > m_col - 1){
        return false;
    }
    if (step->gy < 0 || step->gy > m_row - 1){
        return false;
    }
    if (m_data[step->gx][step->gy] < 0) {
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
    // 查找selectStep周边节点
    // 左
    Step* leftStep = createStep(step->gx - 1, step->gy, step);
    if (checkStep(leftStep)) {
        m_openList.push_back(leftStep);
//        m_data[leftStep->gy][leftStep->gx] = leftStep->f;
    }
    // 右
    Step* rightStep = createStep(step->gx + 1, step->gy, step);
    if (checkStep(rightStep)) {
        m_openList.push_back(rightStep);
//        m_data[rightStep->gy][rightStep->gx] = rightStep->f;
    }
    
    // 上
    Step* upStep = createStep(step->gx, step->gy + 1, step);
    if (checkStep(upStep)) {
        m_openList.push_back(upStep);
//        m_data[upStep->gy][upStep->gx] = upStep->f;
    }
    
    // 下
    Step* downStep = createStep(step->gx, step->gy - 1, step);
    if (checkStep(downStep)) {
        m_openList.push_back(downStep);
//        m_data[downStep->gy][downStep->gx] = downStep->f;
    }
}
Step* AStar::rollbackParentStep()
{
    
}