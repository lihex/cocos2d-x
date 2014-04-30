//
// Created by bruce xiao on 8/21/13.
//
// To change the template use AppCode | Preferences | File Templates.
//

#include "CCActionIntervalForJs.h"

NS_CC_BEGIN

CCActionIntervalForJs::CCActionIntervalForJs()
: m_bIsStartWithTarget(false)
, m_bIsRunning(false)
{
    CCScriptEngineProtocol* pEngine = CCScriptEngineManager::sharedManager()->getScriptEngine();
    m_eScriptType = pEngine != NULL ? pEngine->getScriptType() : kScriptTypeNone;
}

CCActionIntervalForJs::~CCActionIntervalForJs()
{
}

void CCActionIntervalForJs::startWithTarget(cocos2d::CCNode *pTarget)
{
    if (m_bIsStartWithTarget == false)
    {
        m_bIsStartWithTarget = true;
        m_bIsRunning = true;
        
        CCActionInterval::startWithTarget(pTarget);
        if (kScriptTypeNone != m_eScriptType){
            CCScriptEngineManager::sharedManager()->getScriptEngine()->executeCCActionStartWithTargetEvent(this, pTarget);
        }
    }
}

void CCActionIntervalForJs::update(float time)
{
    if (kScriptTypeNone != m_eScriptType){
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeCCActionUpdateEvent(this, time);
    }
}

void CCActionIntervalForJs::stop(){
    if (m_bIsRunning){
        m_bIsRunning = false;
        if (kScriptTypeNone != m_eScriptType){
            CCScriptEngineManager::sharedManager()->getScriptEngine()->executeCCActionStopEvent(this);
        }
        CCActionInterval::stop();
    }
}

NS_CC_END
