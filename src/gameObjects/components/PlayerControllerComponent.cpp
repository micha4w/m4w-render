#include "PlayerControllerComponent.h"

#include "Context.h"
#include "Window.h"
#include "GameObject.h"

m4w::PlayerControllerComponent::PlayerControllerComponent (float speed, float sensitvity, uint16_t moveForward, uint16_t moveLeft, uint16_t moveBack, uint16_t moveRight, uint16_t moveUp, uint16_t moveDown)
    : m_Speed(speed), m_Sensitivity(sensitvity), m_MoveForward(moveForward), m_MoveBack(moveBack), m_MoveRight(moveRight), m_MoveLeft(moveLeft), m_MoveUp(moveUp), m_MoveDown(moveDown)
{ }

void m4w::PlayerControllerComponent::Update (float seconds) {
    m4w::Pointer<Window>& window = g_Context.m_Window;
    if ( !window->IsFocused() || !window->IsMouseGrabbed() )
        return;

    auto [newX, newY] = window->GetMousePosition();

    newX = window->GetWidth()/2 - newX;
    newY = window->GetHeight()/2 - newY;

    m_Owner->Rotate(m4w::Angle::Radians(newX * m_Sensitivity), m4w::Angle::Radians(newY * m_Sensitivity));

    glm::vec3 move(0.f, 0.f, 0.f);
    move.z = window->IsKeyPressed(m_MoveForward) - window->IsKeyPressed(m_MoveBack);
    move.x = window->IsKeyPressed(m_MoveLeft) - window->IsKeyPressed(m_MoveRight);
    move.y = window->IsKeyPressed(m_MoveUp) - window->IsKeyPressed(m_MoveDown);

    m_Owner->Walk(seconds * m_Speed * move);
}


