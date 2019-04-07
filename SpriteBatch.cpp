#include "SpriteBatch.h"

using namespace sf;
using namespace std;

SpriteBatch::SpriteBatch(const Texture& tex, unsigned int s):
	_vertices(s * 4), _texture(tex), _spriteNum(0)
{
	Vector2f texSize = static_cast<Vector2f>( _texture.getSize());
	for (auto i = 0u; i < _vertices.size(); i += 4)
	{
		_vertices[i].texCoords = { 0, 0 };
		_vertices[i + 1].texCoords = { texSize.x, 0 };
		_vertices[i + 2].texCoords = texSize;
		_vertices[i + 3].texCoords = { 0, texSize.y };
	}
}

	const std::vector<sf::Vertex>& SpriteBatch::getVertices() const
	{
		return _vertices;
	}

	array<Vertex*, 4> SpriteBatch::addSprite()
	{
		if ((_spriteNum + 1) * 4 <= _vertices.size())
		{
			unsigned int s = _spriteNum * 4;
			_spriteNum++;
			return { &_vertices[s], &_vertices[s + 1], &_vertices[s + 2], &_vertices[s + 3] };
		}
		else
			return { nullptr };
	}

	Vector2u SpriteBatch::getTextureSize() const
	{
		return  _texture.getSize();
	}

	void SpriteBatch::draw(RenderTarget& target, RenderStates states) const
	{
		states.texture = &_texture;
		target.draw(_vertices.data(), _spriteNum * 4, Quads, states);
	}
