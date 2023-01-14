#include <renderer/camera/CameraController.h>

#include <math/Math.h>
#include <renderer/camera/Camera.h>

CameraController::CameraController() :
	camera(nullptr), movementSpeed(0), scrollSensitivity(0), cursorSensitivity(0), 
	dDistance(0), dYaw(0), dPitch(0)
{}

CameraController::CameraController(Camera* camera, float movementSpeed, float mouseSensitivity, float cursorSensitivity) :
	camera(camera), movementSpeed(movementSpeed), 
	scrollSensitivity(mouseSensitivity), cursorSensitivity(cursorSensitivity),
	dDistance(0), dYaw(0), dPitch(0)
{}

CameraController::CameraController(CameraController&& other) noexcept
{
	*this = std::move(other);
}

CameraController& CameraController::operator=(CameraController&& other) noexcept
{
	if (this == &other) return *this;

	camera = std::exchange(other.camera, nullptr);
	movementSpeed = std::exchange(other.movementSpeed, 0.0f);
	scrollSensitivity = std::exchange(other.scrollSensitivity, 0.0f);
	cursorSensitivity = std::exchange(other.scrollSensitivity, 0.0f);
	dDistance = std::exchange(other.dDistance, 0.0f);
	dYaw = std::exchange(other.dYaw, 0.0f);
	dPitch = std::exchange(other.dPitch, 0.0f);

	return *this;
}

void CameraController::update()
{
	const float minimalDistance = 0.1f;

	float distance = getDistance() + dDistance;
	if (distance < minimalDistance) distance = minimalDistance;

	float yaw = getYaw() + dYaw;
	float pitch = Math::Clamp(getPitch() + dPitch, -89.0f, 89.0f);

	setPosition(distance, yaw, pitch);
	setAngles(yaw, pitch);

	dDistance *= decay;
	dYaw *= decay;
	dPitch *= decay;
}

void CameraController::onMouseScroll(float offset)
{
	dDistance = -offset*scrollSensitivity;
}

void CameraController::onCursorMove(int deltaX, int deltaY)
{
	if (Mouse::GetInstance().isRightButtonDown())
	{
		dYaw = deltaX * cursorSensitivity;
		dPitch = deltaY * cursorSensitivity;
	}
}

float CameraController::getDistance()
{
	return camera->position.length();
}

float CameraController::getYaw()
{
	return Math::Arctan2(camera->position.z, camera->position.x);
}

float CameraController::getPitch()
{
	return Math::Arcsin(camera->position.y / getDistance());
}

void CameraController::setPosition(float distance, float yaw, float pitch)
{
	float x = distance * Math::Cos(pitch) * Math::Cos(yaw);
	float y = distance * Math::Sin(pitch);
	float z = distance * Math::Cos(pitch) * Math::Sin(yaw);

	camera->position = { x, y, z, 0 };
}

void CameraController::setAngles(float yaw, float pitch)
{
	camera->setYaw(yaw + 180);
	camera->setPitch(-pitch);
}

void CameraController::setDistance(float distance)
{
	setPosition(distance, getYaw(), getPitch());
}

void CameraController::setPitch(float newPitch) {
	setPosition(getDistance(), getYaw(), newPitch);
}

void CameraController::setYaw(float newYaw) {
	setPosition(getDistance(), newYaw, getPitch());
}