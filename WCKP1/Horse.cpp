#include "Horse.h"
#include "Input.h"

Horse::Horse(ID3D11Device* device) :
	GameObject(device, 41, 221, 0, &m_Sprite),
	m_Sprite(2, 5, { "Horse0", "Horse1" }),
	m_IsMoving(false),
	m_Direction(XM_PIDIV2),
	m_Speed(200)
{
	m_Sprite.setIndex(0, 1);
}

void Horse::update(float deltaTime)
{
	Input& input = *Input::getInstance();

	if (input.getKey('W'))
	{
		if (!m_IsMoving)
		{
			m_Sprite.setIndex(0, 2);
			m_IsMoving = true;
		}

		float deltaX = XMScalarCos(m_Direction) * m_Speed * deltaTime;
		float deltaY = XMScalarSin(m_Direction) * m_Speed * deltaTime;

		setPosition({ getPosition().x + deltaX, getPosition().y + deltaY });
	}
	else if (input.getKey('S'))
	{
		if (!m_IsMoving)
		{
			m_Sprite.setIndex(0, 2);
			m_IsMoving = true;
		}

		float deltaX = XMScalarCos(m_Direction + XM_PI) * m_Speed * deltaTime;
		float deltaY = XMScalarSin(m_Direction + XM_PI) * m_Speed * deltaTime;

		setPosition({ getPosition().x + deltaX, getPosition().y + deltaY });
	}
	else
	{
		if (m_IsMoving)
		{
			m_Sprite.setIndex(0, 1);
			m_IsMoving = false;
		}
	}

	if (input.getKey(VK_LEFT))
	{
		m_Direction += 0.5 * deltaTime;
	}

	if (input.getKey(VK_RIGHT))
	{
		m_Direction -= 0.5 * deltaTime;
	}

	setAngle(m_Direction - XM_PIDIV2);
}