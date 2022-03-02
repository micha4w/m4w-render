#pragma once

class Component {
public:
    class GameObject* m_Owner;

    virtual void Update(unsigned int microSeconds);
};