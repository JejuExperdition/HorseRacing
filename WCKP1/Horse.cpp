#include "Horse.h"

Horse::Horse(ID3D11Device* device) :
	GameObject(device, 82, 442, 0, &m_Sprite),
	m_Sprite(2, 3.0f, { "Horse1", "Horse2" })
{

}
