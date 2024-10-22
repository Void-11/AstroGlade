namespace ly
{
    class Application;
    class World
    {
    public:
        
        World(Application* owningApp);

        void BeginPlayInternal();
        void TickInternal(float deltaTime);

        virtual ~World();

    private:

        Application* mOwningApp;
        bool mBeginPlay;
        void BeginPlay();
        void Tick(float deltaTime);
    };
}