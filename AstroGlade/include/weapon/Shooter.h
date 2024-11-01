#pragma once

namespace ly
{
    class Actor;
    class Shooter
    {
    public:

        void Shoot();

        virtual bool CanShot() const { return true; }
        virtual bool IsOnCoolDown() const { return false; }
        Actor* GetOwner() const { return mOwner; }

    protected:

        Shooter(Actor* owner);

    private:

        virtual void ShootExecution() = 0;
        Actor* mOwner;
    };
}
