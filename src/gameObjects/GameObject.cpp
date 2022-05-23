#include "GameObject.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "Context.h"
#include "UUIDMap.h"

#include "Shader.h"


m4w::GameObject::GameObject (const glm::vec3& position)
    : m_Position(position), m_Velocity({ 0.f, 0.f, 0.f }),
      m_MeshID(-1), m_CameraID(-1), m_LightID(-1), m_RecalculateView(false), m_Scale(1.f)
{
    this->SetRotation(m4w::Angle(), m4w::Angle());
    m_ID = g_Context.m_Objects.Add(this);
}

m4w::GameObject::~GameObject () {
    g_Context.m_Objects.Remove(m_ID);

    if ( HasCamera() ) g_Context.m_Cameras.Remove(m_CameraID);
    if ( HasLight() ) g_Context.m_Lights.Remove(m_LightID);
    if ( HasMesh() ) g_Context.m_Meshes.Remove(m_MeshID);
}


glm::vec3 operator* (const glm::vec3& vec, unsigned int mul) {
    return {vec.x * mul, vec.y * mul, vec.z * mul};
}

void m4w::GameObject::Update (float seconds) {
    for ( Component* component : m_Components ) {
        component->Update(seconds);
    }

    m_Position += m_Velocity * seconds;

    if ( m_RecalculateView ) {
        if ( this->HasCamera() ) {
            m_Camera->m_Position = m_Position;
            m_Camera->m_Offset = m_Rotation;
            m_Camera->m_Recalculate = true;
        }

        if ( this->HasMesh() ) {
            m_Mesh->m_ModelMatrix = glm::mat4(1.f);
            m_Mesh->m_ModelMatrix = glm::translate(m_Mesh->m_ModelMatrix, m_Position);
            m_Mesh->m_ModelMatrix = glm::scale(m_Mesh->m_ModelMatrix, glm::vec3(m_Scale));
            m_Mesh->m_ModelMatrix = glm::rotate(m_Mesh->m_ModelMatrix, m_Pitch.GetRadians(), {1, 0, 0});
            m_Mesh->m_ModelMatrix = glm::rotate(m_Mesh->m_ModelMatrix, m_Yaw.GetRadians(), {0, 1, 0});
            //m_Mesh->m_ModelMatrix = glm::rotate(m_Mesh->m_ModelMatrix, m_Roll, {0, 0, 1});

        }
        m_RecalculateView = false;
    }
}

void m4w::GameObject::Rotate (const m4w::Angle& dYaw, const m4w::Angle& dPitch) {
    if ( dYaw.GetRadians() || dPitch.GetRadians() ) SetRotation(m_Yaw + dYaw, m_Pitch + dPitch);
}

void m4w::GameObject::SetRotation (const m4w::Angle& yaw, const m4w::Angle& pitch) {    
    m_Yaw = yaw;
    m_Pitch = pitch;

    m_Pitch.ClampDegrees( -89.9, 89.9 );

    float y = m_Pitch.Sin();

    float cY = m_Pitch.Cos();
    float x = -m_Yaw.Sin() * cY;
    float z = -m_Yaw.Cos() * cY;

    m_Rotation = { x, y, z };
    m_RecalculateView = true;
}

void m4w::GameObject::Walk (const glm::vec3& vector) {
    glm::vec3 direction = { m_Rotation.x, 0.f, m_Rotation.z };
    glm::vec3 strafe = glm::normalize(glm::cross({ 0.f, 1.f, 0.f }, direction));

    this->Move( direction * vector.z + strafe * vector.x + glm::vec3(0.f, 1.f, 0.f) * vector.y );
}

void m4w::GameObject::Move (const glm::vec3& vector) {
    if ( vector.x || vector.y || vector.z ) {
        this->Teleport(m_Position + vector);
    }
}

void m4w::GameObject::Teleport (const glm::vec3& position) {
    m_Position = position;
    m_RecalculateView = true;
}

void m4w::GameObject::Accelerate (const glm::vec3& acceleration) {
    m_Velocity += acceleration;
}

void m4w::GameObject::Scale (float factor) {
    this->SetScale(m_Scale * factor);
}

void m4w::GameObject::SetScale (float scale) {
    m_Scale = scale;
    m_RecalculateView = true;
}


glm::vec3 m4w::GameObject::GetPosition() { return m_Position; }
std::pair<m4w::Angle, m4w::Angle> m4w::GameObject::GetRotation() { return { m_Yaw, m_Pitch }; }
float m4w::GameObject::GetScale () { return m_Scale; }

void m4w::GameObject::SetMesh (Mesh* mesh) {
    if ( this->HasMesh() ) {
        g_Context.m_Meshes.Remove(m_MeshID);
    }

    m_MeshID = g_Context.m_Meshes.Add(std::forward<Mesh>(*mesh));
    m_Mesh = g_Context.m_Meshes.Get(m_MeshID);
}

void m4w::GameObject::SetLight (Light* light) {
    if ( this->HasLight() ) {
        g_Context.m_Lights.Remove(m_LightID);
    }

    m_LightID = g_Context.m_Lights.Add(std::forward<Light>(*light));
    m_Light = g_Context.m_Lights.Get(m_LightID);
}

void m4w::GameObject::SetCamera (Camera* camera) {
    if ( this->HasCamera() ) {
        g_Context.m_Cameras.Remove(m_CameraID);
    }

    m_RecalculateView = true;
    m_CameraID = g_Context.m_Cameras.Add(std::forward<Camera>(*camera));
    m_Camera = g_Context.m_Cameras.Get(m_CameraID);
}


void m4w::GameObject::AddComponent (m4w::Pointer<Component> component) {
    component->m_Owner = this;
    m_Components.push_back(component);
}


bool m4w::GameObject::HasMesh () { return m_MeshID != -1; }
bool m4w::GameObject::HasLight () { return m_LightID != -1; }
bool m4w::GameObject::HasCamera () { return m_CameraID != -1; }


m4w::Mesh* m4w::GameObject::GetMesh() {
    return m_Mesh;
}

m4w::Light* m4w::GameObject::GetLight() {
    return m_Light;
}

m4w::Camera* m4w::GameObject::GetCamera() {
    return m_Camera;
}

