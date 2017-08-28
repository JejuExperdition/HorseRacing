#include "Boost.h"
#include "Graphics.h"

Boost::Boost(const XMFLOAT2& pos) :
	Boost(std::move(pos))
{

}
Boost::Boost(const XMFLOAT2&& pos) :
	GameObject(Graphics::getInstance()->getDevice(), 128, 128, 1, &m_Sprite),
	m_Sprite("Boost")
{
	setPosition(pos);
}