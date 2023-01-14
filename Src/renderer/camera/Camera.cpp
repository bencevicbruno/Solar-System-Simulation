#pragma once

#include <devices/Window.h> // this includes glew too
#include <math/Math.h>

#include "renderer/camera/Camera.h"
#include "renderer/camera/CameraController.h"

#include "utils/Utils.h"

const Camera& Camera::getActiveCamera()
{
	if (activeCamera == nullptr)
	{
		Utils::CrashWithLog("No camera bound!");
	}

	return *activeCamera;
}

Camera::Camera():
	position({20, 20, 20, 0}),
	yaw(0), pitch(0),
	zoom(90.0f), // BACK TO 80.0F
	controller(CameraController(this, 0.01f, 1.0f, 0.1f))
{
	update();
}

Vector Camera::getPosition() const
{
	return position;
}

float Camera::getYaw() const
{
	return yaw;
}

float Camera::getPitch() const
{
	return pitch;
}

float Camera::getZoom() const
{
	return zoom;
}

void Camera::setYaw(float newYaw)
{
	yaw = newYaw;
}

void Camera::setPitch(float newPitch)
{
	pitch = Math::Clamp(newPitch, -89, 89);
}

void Camera::setZoom(float newZoom)
{
	if (newZoom < 10) newZoom = 10;

	zoom = newZoom;
}

void Camera::update()
{
	controller.update();
	updateViewVectors();
}

Matrix Camera::getViewMatrix() const
{
	return {
		rightVector.x, rightVector.y, rightVector.z, - Vector::DotProduct(rightVector, position),
		upVector.x, upVector.y, upVector.z, -Vector::DotProduct(upVector, position),
		-frontVector.x, -frontVector.y, -frontVector.z, Vector::DotProduct(frontVector, position),
		0, 0, 0, 1 };
}

Matrix Camera::getProjectionMatrix() const
{
	const float far = 10000.0f, near = 0.1f;

	Matrix matrix;

	float fov = Math::ToRadians(zoom);
	float aspectRatio = (float) Window::WIDTH / Window::HEIGHT;
	float tanHalfFov = std::tan(fov / 2);

	matrix.data[0][0] = 1 / (aspectRatio * tanHalfFov);
	matrix.data[1][1] = 1 / tanHalfFov;
	matrix.data[2][2] = -(far + near) / (far - near);
	matrix.data[2][3] = -2 * far * near / (far - near);
	matrix.data[3][2] = -1;

	return matrix;
}

void Camera::bind() const
{
	activeCamera = this;
}

const Camera* Camera::activeCamera = nullptr;

void Camera::updateViewVectors()
{
	updateFrontVector();
	updateRightVector();
	updateUpVector();
}

void Camera::updateFrontVector()
{
	frontVector.x = Math::Cos(yaw) * Math::Cos(pitch);
	frontVector.y = Math::Sin(pitch);
	frontVector.z = Math::Sin(yaw) * Math::Cos(pitch);

	frontVector.normalize();
}

void Camera::updateRightVector()
{
	rightVector = Vector::CrossProduct(frontVector, Vector::up());
	rightVector.normalize();
}

void Camera::updateUpVector()
{
	// no need to normalize - both unit & perpendicular vectors
	upVector = Vector::CrossProduct(rightVector, frontVector);
}

void Camera::onMouseScroll(float offset)
{
	controller.onMouseScroll(offset);

	updateViewVectors();
}

void Camera::onCursorMove(int deltaX, int deltaY)
{
	controller.onCursorMove(deltaX, deltaY);

	updateViewVectors();
}

