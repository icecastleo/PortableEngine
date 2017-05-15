#pragma once
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <DirectXMath.h>
#include "Text.h"
#include <vector>

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
	void DrawLiveText(const wchar_t*, DirectX::XMFLOAT2);

	void AddText(const wchar_t*, DirectX::XMFLOAT2);
	void ClearText();

private:

	// 2D rendering stuff
	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFontArial;

	ID3D11ShaderResourceView* fontSRV;

	const wchar_t* path;
	const wchar_t* textToDraw;

	std::vector<textObject> textList;
};