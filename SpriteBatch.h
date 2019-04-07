#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <array>
#include <vector>

using namespace sf;
using namespace std;


class SpriteBatch : public Drawable
{
public:
	SpriteBatch(const Texture& tex, unsigned int s);

	const vector<Vertex>& getVertices() const;

	array<Vertex*, 4> addSprite();

	Vector2u getTextureSize() const;

private:
	virtual void draw(RenderTarget& target, RenderStates states) const;

	vector<Vertex> _vertices;

	const Texture& _texture;

	unsigned int _spriteNum;
};



