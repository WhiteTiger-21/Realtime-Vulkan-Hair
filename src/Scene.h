#pragma once

#include <glm/glm.hpp>
#include <chrono>

#include "Model.h"
#include "Strand.h"

using namespace std::chrono;

struct Time {
    float deltaTime = 0.0f;
    float totalTime = 0.0f;
};

struct Collider {
	glm::vec3 center;
	float radius;
};

class Scene {
private:
    Device* device;
    
    VkBuffer timeBuffer;
    VkDeviceMemory timeBufferMemory;
    Time time;

    void* mappedData;

    std::vector<Model*> models;
    std::vector<Hair*> hair;

	std::vector<Collider> colliders;
	VkBuffer collidersBuffer;
	VkDeviceMemory collidersBufferMemory;

	high_resolution_clock::time_point startTime = high_resolution_clock::now();

public:
    Scene() = delete;
    Scene(Device* device);
    ~Scene();

    const std::vector<Model*>& GetModels() const;
    const std::vector<Hair*>& GetHair() const;
    const std::vector<Collider>& GetColliders() const;
    
    void AddModel(Model* model);
    void AddHair(Hair* hair);
    void AddCollider(Collider collider);

    VkBuffer GetTimeBuffer() const;
    VkBuffer GetCollidersBuffer() const;

	void CreateCollidersBuffer(VkCommandPool commandPool);

    void UpdateTime();
};
