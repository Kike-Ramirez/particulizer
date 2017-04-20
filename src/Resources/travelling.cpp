#include "travelling.h"

Travelling::Travelling()
{

}

void Travelling::setupTravelling(ofVec3f position_, ofVec3f size_)
{
    modeTravelling = 0;
    maxModeTravelling = 4;
    modeTargeting = 0;
    maxModeTargeting = 4;
    offsetTime = 0.0;
    position.set(position_);
    size.set(size_);

}

void Travelling::updateTravelling(float elapsedTime_, vector<float> &cameraPanel_)
{

    float elapsedTime = (offsetTime + elapsedTime_);

    float cameraRadio = size.x * 1.5 * cameraPanel_[0] * (1.0 - 1.0 * cameraPanel_[3] * ofNoise(elapsedTime));
    float cameraHeight = 1.0 + size.y * cameraPanel_[1] * (1.0 - 1.0 * cameraPanel_[3] * ofNoise(elapsedTime + 5.0));

    float cameraSideX = size.x * cameraPanel_[0] * (1.0 - 1.0 * cameraPanel_[3] * ofNoise(elapsedTime + 10.0));
    float cameraSideY = size.y * cameraPanel_[0] * (1.0 - 1.0 * cameraPanel_[3] * ofNoise(elapsedTime + 15.0));
    float cameraSideZ = size.z * cameraPanel_[1] * (1.0 - 1.0 * cameraPanel_[3] * ofNoise(elapsedTime + 20.0));


    // Check changes of modes from NanoKontrol
    if (cameraPanel_[2] == 1.0)
    {
        modeTravelling ++;
        if (modeTravelling >= maxModeTravelling) modeTravelling = 0;

    }

    if (cameraPanel_[4] == 1.0)
    {
        modeTargeting++;
        if (modeTargeting >= maxModeTargeting) modeTargeting = 0;

    }


    // Update geometrical values of Travelling according to selected mode
   if (modeTravelling == 0)
        {
            // Fixed Position

            float cx = position.x + cameraRadio;
            float cy = position.y - cameraHeight;
            float cz = position.z;

            setPosition(cx, cy, cz);
        }

    else if (modeTravelling == 1)
        {
            // Circular Movement

            float cx = position.x + cameraRadio * cos(elapsedTime * 360 / 2 / PI);
            float cy = position.y - cameraHeight;
            float cz = position.z + cameraRadio * sin(elapsedTime * 360 / 2 / PI);

            this->setPosition(cx, cy, cz);

        }

    else if (modeTravelling == 2)
        {
            // Esferical Movement

            float cx = position.x + cameraRadio * cos(elapsedTime * 360 / 2 / PI) * sin(elapsedTime * 360 / 2 / PI / 10);
            float cy = position.y + cameraHeight * cos(elapsedTime * 360 / 2 / PI / 10);
            float cz = position.z + cameraRadio * sin(elapsedTime * 360 / 2 / PI) * sin(elapsedTime * 360 / 2 / PI / 10);

            this->setPosition(cx, cy, cz);
        }

    else if (modeTravelling == 3)

        {
            // Free 3D Perlin Movement

            float cx = position.x + cameraSideX * (-0.5 + ofNoise(elapsedTime));
            float cy = position.y + cameraSideY * (-0.5 + ofNoise(elapsedTime + 10));
            float cz = position.z + cameraSideZ * (-0.5 + ofNoise(elapsedTime + 20));

            this->setPosition(cx, cy, cz);

        }


    // Update geometrical values of target according to selected mode
    if (modeTargeting == 0)
        {
            // Fixed Position

            float cx = position.x;
            float cy = position.y;
            float cz = position.z;

            this->lookAt(ofVec3f(cx, cy, cz));

        }

     else if (modeTargeting == 1)
        {
            // Cilindrical Movement
            float cx = position.x + cameraRadio * cos(elapsedTime * 360 / 2 / PI + 180.0);
            float cy = position.y;
            float cz = position.z + cameraRadio * sin(elapsedTime * 360 / 2 / PI + 180.0);

            this->lookAt(ofVec3f(cx, cy, cz));

        }

     else if (modeTargeting == 2)
        {
            // Esferical Movement

            float cx = cameraRadio * cos(elapsedTime * 360 / 2 / PI) * sin(elapsedTime * 360 / 2 / PI / 10);
            float cy = 0;
            float cz = cameraRadio * sin(elapsedTime * 360 / 2 / PI) * sin(elapsedTime * 360 / 2 / PI / 10);

            this->lookAt(ofVec3f(cx, cy, cz));

        }
     else if (modeTargeting == 3)
        {
            // Free 3D Perlin Movement

            float cx = position.x + cameraSideX * (-0.5 + ofNoise(elapsedTime + 30));
            float cy = position.y + cameraSideY * (-0.5 + ofNoise(elapsedTime + 40));
            float cz = position.z + cameraSideZ * (-0.5 + ofNoise(elapsedTime + 50));

            lookAt(ofVec3f(cx, cy, cz));

        }

    cout << this->getPosition() << " " << this->getLookAtDir() << " " << modeTargeting << " " << modeTravelling << endl;


}

void Travelling::moveTravelling(int delta_)
{

    offsetTime += delta_;

}

void Travelling::setModeTravelling(int mode_)
{

    modeTravelling = mode_;
}

void Travelling::setModeTargeting(int mode_)
{
    modeTargeting = mode_;
}
