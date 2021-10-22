#pragma once

#include <vector>

#include <glm/vec3.hpp>

#include "Angle.h"
#include "Pointer.h"

#include "Component.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "Context.h"

class GameObject {
private:
    Context& m_Context;

    unsigned int m_ID;

    bool m_RecalculateView;
    float m_Scale;
    m4w::Angle m_Yaw, m_Pitch;

    glm::vec3 m_Rotation;
    glm::vec3 m_Position;
    glm::vec3 m_Velocity;

    Mesh* m_Mesh;
    Camera* m_Camera;
    Light* m_Light;

    int m_LightID, m_MeshID, m_CameraID;
    // Light, Mesh, (collisionMesh), Camera

    std::vector<m4w::Pointer<Component>> m_Components;
public:
    const glm::vec3 m_WorldUp = { 0.f, 1.f, 0.f };

    GameObject(Context& context, const glm::vec3& position = { 0.f, 0.f, 0.f });
    ~GameObject();

    void Update(unsigned int microSeconds);

    void Rotate(const m4w::Angle& dYaw, const m4w::Angle& dPitch);
    void SetRotation(const m4w::Angle& yaw, const m4w::Angle& pitch);

    void Walk(const glm::vec3& vector);
    void Move(const glm::vec3& vector);
    void Teleport(const glm::vec3& position);
    void Accelerate(const glm::vec3& acceleration);

    void Scale(float factor);
    void SetScale(float scale);

    glm::vec3 GetPosition();
    std::pair<m4w::Angle, m4w::Angle> GetRotation();
    float GetScale();

    void SetMesh(Mesh* mesh);
    void SetLight(Light* light);
    void SetCamera(Camera* camera);


    template <typename... Args>
    void CreateMesh(Args&&... args){
        if ( this->HasMesh() ) {
            m_Context.m_Meshes.Remove(m_MeshID);
        }

        m_MeshID = m_Context.m_Meshes.Create(std::forward_as_tuple(args...));
        m_Mesh = m_Context.m_Meshes.Get(m_MeshID);
    }
     
    template <typename... Args>
    void CreateLight(Args&&... args){
        if ( this->HasLight() ) {
            m_Context.m_Lights.Remove(m_LightID);
        }

        m_LightID = m_Context.m_Lights.Create(std::forward_as_tuple(args...));
        m_Light = m_Context.m_Lights.Get(m_LightID);
    }

    template <typename... Args>
    void CreateCamera(Args&&... args){
        if ( this->HasCamera() ) {
            m_Context.m_Cameras.Remove(m_CameraID);
        }

        m_RecalculateView = true;
        m_CameraID = m_Context.m_Cameras.Create(std::forward_as_tuple(args...));
        m_Camera = m_Context.m_Cameras.Get(m_CameraID);
    }

    void AddComponent(m4w::Pointer<Component> component);

    Mesh* GetMesh();
    Light* GetLight();
    Camera* GetCamera();

    bool HasMesh();
    bool HasLight();
    bool HasCamera();
};