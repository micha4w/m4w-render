#include "PlayerControllerComponent.h"

#include "Context.h"
#include "Window.h"
#include "GameObject.h"

PlayerControllerComponent::PlayerControllerComponent(float speed, float sensitvity, uint16_t moveForward, uint16_t moveLeft, uint16_t moveBack, uint16_t moveRight, uint16_t moveUp, uint16_t moveDown)
    : m_Speed(speed), m_Sensitivity(sensitvity), m_MoveForward(moveForward), m_MoveBack(moveBack), m_MoveRight(moveRight), m_MoveLeft(moveLeft), m_MoveUp(moveUp), m_MoveDown(moveDown)
{ }

void PlayerControllerComponent::Update(unsigned int microSeconds) {
    if ( !g_Context.m_Window->IsFocused() )
        return;

    m4w::Pointer<Window> window = g_Context.m_Window;
    auto [newX, newY] = window->GetMousePosition();

    newX = window->GetWidth()/2 - newX;
    newY = window->GetHeight()/2 - newY;

    m_Owner->Rotate(m4w::Angle::Radians(newX * m_Sensitivity), m4w::Angle::Radians(newY * m_Sensitivity));

    glm::vec3 move(0.f, 0.f, 0.f);
    move.z = window->GetKeyPressed(m_MoveForward) - window->GetKeyPressed(m_MoveBack);
    move.x = window->GetKeyPressed(m_MoveLeft) - window->GetKeyPressed(m_MoveRight);
    move.y = window->GetKeyPressed(m_MoveUp) - window->GetKeyPressed(m_MoveDown);

    m_Owner->Walk(m_Speed * move * 0.01f);
}


