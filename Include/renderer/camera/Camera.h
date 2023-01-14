#pragma once

#include <devices/Keyboard.h>
#include <devices/Cursor.h>
#include <devices/Mouse.h>
#include <math/Matrix.h>
#include <math/Vector.h>

#include <renderer/camera/CameraController.h>

class Camera : ICursorMovementListener, IMouseScrollListener
{
public:
	static const Camera& getActiveCamera();

	Vector position;

	Camera();

	Vector getPosition() const;
	float getYaw() const;
	float getPitch() const;
	float getZoom() const;

	void setYaw(float newYaw);
	void setPitch(float newPitch);
	void setZoom(float newZoom);

	void update();

	Matrix getViewMatrix() const;
	Matrix getProjectionMatrix() const;

	void bind() const;

	CameraController controller;
private:
	static const Camera* activeCamera;

	

	float yaw;
	float pitch;
	float zoom;

	Vector frontVector, rightVector, upVector;

	Camera(const Camera& other) = delete;
	Camera(Camera&& other) = delete;
	void operator=(const Camera& other) = delete;
	void operator=(Camera&& other) = delete;

	void updateViewVectors();
	void updateFrontVector();
	void updateRightVector();
	void updateUpVector();

	void onMouseScroll(float offset) override;
	void onCursorMove(int deltaX, int deltaY) override;
};

