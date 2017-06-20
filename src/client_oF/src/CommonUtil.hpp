#include "ofMain.h"

class SmoothValue{
public:
    
    SmoothValue():mSpeed(0.04),mValue(0),mTarget(0){
        
    }
    
    void update(){
        mValue += (mTarget - mValue) * mSpeed;
    }
    
    void to(float target){
        mTarget = target;
    }
    
    void set(float target){
        mValue = target;
        mTarget = target;
    }
    
    float get(){
        return mValue;
    };
    
    void setSpeed(float speed){
        mSpeed = speed;
    }
    
private:
    float mValue;
    float mTarget;
    float mSpeed;
};

class SmoothPoint : public ofPoint{
public:
    
    SmoothPoint():mSpeed(0.04){
        
    }
    
    void update(){
        this->x += (mTarget.x - this->x) * mSpeed;
        this->y += (mTarget.y - this->y) * mSpeed;
        this->z += (mTarget.z - this->z) * mSpeed;
    }
    
    void to(ofPoint target){
        mTarget = target;
    }
    
    void set(ofPoint target){
        mTarget = target;
        ofPoint::set(target);
    }
    
    void setSpeed(float speed){
        mSpeed = speed;
    }
    
private:
    ofPoint mTarget;
    float mSpeed;
};
