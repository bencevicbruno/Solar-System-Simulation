#pragma once

#include <math/Vector.h>

class Camera;

class CameraController
{
public:
	CameraController();
	CameraController(Camera* camera, float movementSpeed, float mouseSensitivity, float cursorSensitivity);
	CameraController(CameraController&& other) noexcept;

	CameraController& operator=(CameraController&& other) noexcept;

	void update();
	void onMouseScroll(float offset);
	void onCursorMove(int deltaX, int deltaY);

	void setDistance(float distance);
	void setPitch(float newPitch);
	void setYaw(float newYaw);

private:
	Camera* camera;
	float movementSpeed, scrollSensitivity, cursorSensitivity;

	const float decay = 0.95f;
	float dDistance, dYaw, dPitch;

	float getDistance();
	float getYaw();
	float getPitch();

	void setPosition(float distance, float yaw, float pitch);
	void setAngles(float yaw, float pitch);

	CameraController(const CameraController& other) = delete;
	void operator=(const CameraController& other) = delete;
};

