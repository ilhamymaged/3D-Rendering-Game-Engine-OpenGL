#include <memory>
#include <vector>
#include <System.h>

class SystemManager 
{
public:
    template<typename T, typename... Args>
    T& addSystem(Args&&... args)
    {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *ptr;
        systems.push_back(std::move(ptr));
        return ref;
    }

    template<typename T>
    T& getSystem()
    {
        for (auto& s : systems)
        {
            if (auto ptr = dynamic_cast<T*>(s.get()))
                return *ptr;
        }
        throw std::runtime_error("System not found!");
    }
    
    void update(entt::registry& registry, float dt);
    void fireEvents(Event& event);
private:
    std::vector<std::unique_ptr<System>> systems;
};
