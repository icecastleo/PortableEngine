#pragma once
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <DirectXMath.h>

class Text2D
{
public:
	Text2D();
	Text2D(const wchar_t*);
	~Text2D();

	void Init(ID3D11DeviceContext*, ID3D11Device*);

	ID3D11ShaderResourceView* GetSRV();

	void SetText(const wchar_t*);
	void SetupFont();
	void DrawMyText();

private:

	// 2D rendering stuff
	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFontArial;

	ID3D11ShaderResourceView* fontSRV;

	const wchar_t* path;
	const wchar_t* textToDraw;
};