#include "travelling.h"

Travelling::Travelling()
{

}

void Travelling::setupTravelling(ofVec3f position_, ofVec3f size_)
{
    modeTravelling = 0;
    modeTargeting = 0;
    position.set(position_);
    size.set(size_);
}

void Travelling::updateTravelling(int ellapsedTime_, vector<float> &cameraPanel_)
{

    float cameraRadio = size.x * 1.5 * cameraPanel_[0] * (0.5 - 0.5 * cameraPanel_[3] * ofNoise(ellapsedTime_));
    float cameraHeight = -1.0 - size.y * cameraPanel_[1] * (0.5 - 0.5 * cameraPanel_[3] * ofNoise(ellapsedTime_));

    float cameraSideX = size.x * cameraPanel_[0] * (0.5 - 0.5 * cameraPanel_[3] * ofNoise(ellapsedTime_));
    float cameraSideY = size.y * cameraPanel_[0] * (0.5 - 0.5 * cameraPanel_[3] * ofNoise(ellapsedTime_));
    float cameraSideZ = size.z * cameraPanel_[1] * (0.5 - 0.5 * cameraPanel_[3] * ofNoise(ellapsedTime_));


    switch (modeTravelling)
    {
        case 0:
        {
            // Cilinder Movement

            float cx = position.x + cameraRadio * cos(ellapsedTime_ * 360 / 2 / PI);
            float cy = position.y + cameraHeight;
            float cz = position.z + cameraRadio * sin(ellapsedTime_ * 360 / 2 / PI);

            setPosition(cx, cy, cz);


        }
        case 1:
        {
            // Esferical Movement

            float cx = position.x + cameraRadio * cos(ellapsedTime_ * 360 / 2 / PI) * sin(ellapsedTime_ * 360 / 2 / PI / 10);
            float cy = position.y + cameraHeight * cos(ellapsedTime_ * 360 / 2 / PI / 10);
            float cz = position.z + cameraRadio * sin(ellapsedTime_ * 360 / 2 / PI) * sin(ellapsedTime_ * 360 / 2 / PI / 10);

            setPosition(cx, cy, cz);
        }
        case 2:
        {
            // Free 3D Perlin Movement

            float cx = position.x + cameraSideX * (-0.5 + ofNoise(ellapsedTime_));
            float cy = position.y + cameraSideY * (-0.5 + ofNoise(ellapsedTime_ + 10));
            float cz = position.z + cameraSideZ * (-0.5 + ofNoise(ellapsedTime_ + 20));

            setPosition(cx, cy, cz);
        }

    }


    switch (modeTargeting)
    {
        case 0:
        {
            // Cilinder Movement
            float cx = cameraRadio * cos(ellapsedTime_ * 360 / 2 / PI + 180.0);
            float cy = 0;
            float cz = cameraRadio * sin(ellapsedTime_ * 360 / 2 / PI + 180.0);

            lookAt(ofVec3f(cx, cy, cz));

        }
        case 1:
        {
            // Esferical Movement

            float cx = cameraRadio * cos(ellapsedTime_ * 360 / 2 / PI) * sin(ellapsedTime_ * 360 / 2 / PI / 10);
            float cy = cameraHeight * cos(ellapsedTime_ * 360 / 2 / PI / 10);
            float cz = cameraRadio * sin(ellapsedTime_ * 360 / 2 / PI) * sin(ellapsedTime_ * 360 / 2 / PI / 10);

            lookAt(ofVec3f(cx, cy, cz));

        }
        case 2:
        {

            float cx = position.x + cameraSideX * (-0.5 + ofNoise(ellapsedTime_ + 30));
            float cy = position.y + cameraSideY * (-0.5 + ofNoise(ellapsedTime_ + 40));
            float cz = position.z + cameraSideZ * (-0.5 + ofNoise(ellapsedTime_ + 50));

            lookAt(ofVec3f(cx, cy, cz));

        }

    }

}

void Travelling::setModeTravelling(int mode_)
{

    modeTravelling = mode_;
}

void Travelling::setModeTargeting(int mode_)
{
    modeTargeting = mode_;
}
