#include "GameObject.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "Context.h"
#include "UUIDMap.h"

#include "Shader.h"
#include "View.h"


GameObject::GameObject(const glm::vec3& position)
    : m_Position(position), m_Velocity({ 0.f, 0.f, 0.f }),
      m_MeshID(-1), m_CameraID(-1), m_LightID(-1), m_RecalculateView(false)
{
    this->SetRotation(m4w::Angle(), m4w::Angle());
    m_ID = Context::Get()->m_Objects.Add(this);
}

GameObject::~GameObject() {
    Context::Get()->m_Objects.Remove(m_ID);

    if ( HasCamera() ) Context::Get()->m_Cameras.Remove(m_CameraID);
    if ( HasLight() ) Context::Get()->m_Lights.Remove(m_LightID);
    if ( HasMesh() ) Context::Get()->m_Meshes.Remove(m_MeshID);
}


glm::vec3 operator* (const glm::vec3& vec, unsigned int mul) {
    return {vec.x * mul, vec.y * mul, vec.z * mul};
}

void GameObject::Update(unsigned int microSeconds) {
    for ( Component* component : m_Components ) {
        component->Update(microSeconds);
    }

    m_Position += m_Velocity * microSeconds;

    if ( m_RecalculateView ) {
        if ( this->HasCamera() ) {
            m_Camera->m_View->m_Position = m_Position;
            m_Camera->m_View->m_Offset = m_Rotation;
            m_Camera->m_View->m_Recalculate = true;
        }

        if ( this->HasMesh() ) {
            m_Mesh->m_ModelMatrix = glm::mat4(1.f);
            m_Mesh->m_ModelMatrix = glm::translate(m_Mesh->m_ModelMatrix, m_Position);
            m_Mesh->m_ModelMatrix = glm::rotate(m_Mesh->m_ModelMatrix, m_Rotation.x, {1, 0, 0});
            m_Mesh->m_ModelMatrix = glm::rotate(m_Mesh->m_ModelMatrix, m_Rotation.y, {0, 1, 0});
            m_Mesh->m_ModelMatrix = glm::rotate(m_Mesh->m_ModelMatrix, m_Rotation.z, {0, 0, 1});

        }
        m_RecalculateView = false;
    }
}

void GameObject::Rotate(const m4w::Angle& dYaw, const m4w::Angle& dPitch) {
    if ( dYaw.GetRadians() || dPitch.GetRadians() ) SetRotation(m_Yaw + dYaw, m_Pitch + dPitch);
}

void GameObject::SetRotation(const m4w::Angle& yaw, const m4w::Angle& pitch) {    
    m_Yaw = yaw;
    m_Pitch = pitch;

    m_Pitch.ClampDegrees( -89.9, 89.9 );
    float y = m_Pitch.Sin();

    float x = -m_Yaw.Sin();
    float z = -m_Yaw.Cos();

    m_Rotation = { x, y, z };
    m_RecalculateView = true;
}

void GameObject::Walk(const glm::vec3& vector) {
    glm::vec3 direction = { m_Rotation.x, 0.f, m_Rotation.z };
    glm::vec3 strafe = glm::normalize(glm::cross({ 0.f, 1.f, 0.f }, direction));

    this->Move( direction * vector.z + strafe * vector.x + glm::vec3(0.f, 1.f, 0.f) * vector.y );
}

void GameObject::Move(const glm::vec3& vector) {
    if ( vector.x || vector.y || vector.z ) {
        this->Teleport(m_Position + vector);
    }
}

void GameObject::Teleport(const glm::vec3& position) {
    m_Position = position;
    m_RecalculateView = true;
}

void GameObject::Accelerate(const glm::vec3& acceleration) {
    m_Velocity += acceleration;
}

glm::vec3 GameObject::GetPosition() { return m_Position; }
std::pair<m4w::Angle, m4w::Angle> GameObject::GetRotation() { return { m_Yaw, m_Pitch }; }

void GameObject::SetMesh(Mesh* mesh) {
    if ( this->HasMesh() ) {
        Context::Get()->m_Meshes.Remove(m_MeshID);
    }

    m_MeshID = Context::Get()->m_Meshes.Add(std::forward<Mesh>(*mesh));
    m_Mesh = Context::Get()->m_Meshes.Get(m_MeshID);
}

void GameObject::SetLight(Light* light) {
    if ( this->HasLight() ) {
        Context::Get()->m_Lights.Remove(m_LightID);
    }

    m_LightID = Context::Get()->m_Lights.Add(std::forward<Light>(*light));
    m_Light = Context::Get()->m_Lights.Get(m_LightID);
}

void GameObject::SetCamera(Camera* camera) {
    if ( this->HasCamera() ) {
        Context::Get()->m_Cameras.Remove(m_CameraID);
    }

    m_RecalculateView = true;
    m_CameraID = Context::Get()->m_Cameras.Add(std::forward<Camera>(*camera));
    m_Camera = Context::Get()->m_Cameras.Get(m_CameraID);
}


void GameObject::AddComponent(m4w::Pointer<Component> component) {
    component->m_Owner = this;
    m_Components.push_back(component);
}


bool GameObject::HasMesh() { return m_Mesh; }
bool GameObject::HasLight() { return m_Light; }
bool GameObject::HasCamera() { return m_Camera; }


Mesh* GameObject::GetMesh() {
    return m_Mesh;
}

Light* GameObject::GetLight() {
    return m_Light;
}

Camera* GameObject::GetCamera() {
    return m_Camera;
}

