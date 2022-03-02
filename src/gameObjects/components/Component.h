#pragma once

class Component {
public:
    class Context& m_Context;

    class GameObject* m_Owner;

    Component (class Context& context)
        : m_Context(context)
    { }

    virtual void Update(unsigned int microSeconds);
};