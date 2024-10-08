#include"Camera.h"

SDL_Rect Camera::GetViewBox()
{
	return m_ViewBox;
}

Vector2 Camera::GetPosition()
{
	return m_Position;
}

void Camera::SetTarget(std::shared_ptr<BaseObject> target) // Settarget for player (-> Set origin position)
{
	m_target = target;
}

void Camera::Update(float deltaTime)
{
    if (m_target != nullptr)
    {
        // Apply zoom to the view box dimensions
        m_ViewBox.w = SCREEN_WIDTH / m_ZoomFactor;
        m_ViewBox.h = SCREEN_HEIDHT / m_ZoomFactor;

        // Center the camera on the target
        m_ViewBox.x = (m_target->GetPosition().x - m_ViewBox.w / 2);
        m_ViewBox.y = (m_target->GetPosition().y - m_ViewBox.h / 2);

        // Keep the camera in bounds
        if (m_ViewBox.x < 0) m_ViewBox.x = 0;
        if (m_ViewBox.y < 0) m_ViewBox.y = 0;
        if (m_ViewBox.x > (GetLevelWidth() - m_ViewBox.w)) m_ViewBox.x = (GetLevelWidth() - m_ViewBox.w);
        if (m_ViewBox.y > (GetLevelHeight() - m_ViewBox.h)) m_ViewBox.y = (GetLevelHeight() - m_ViewBox.h);

        m_Position = Vector2(m_ViewBox.x, m_ViewBox.y);
    }
}

void Camera::SetZoom(float zoom)
{
    m_ZoomFactor = zoom;
    if (m_ZoomFactor < 0.1f) m_ZoomFactor = 0.1f;  // Prevent excessive zooming in
    if (m_ZoomFactor > 10.0f) m_ZoomFactor = 10.0f; // Prevent excessive zooming out
}


void Camera::SetLevelDimension(int width, int height)
{
	m_levelWidth = width;
	m_levelHeight = height;
}

int Camera::GetLevelWidth()
{
	return m_levelWidth;
}

int Camera::GetLevelHeight()
{
	return m_levelHeight;
}
