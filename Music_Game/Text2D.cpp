#include "Tex2Dt.h"

//---------------------------------------------------------
//Default Constructor using Arial as the default font
//---------------------------------------------------------
Text2D::Text2D()
{
	path = L"Assets/fonts/Arial.spritefont";
}

//---------------------------------------------------------
//Constructor taking a font file path
//---------------------------------------------------------
Text2D::Text2D(const wchar_t* _path)
{
	path = _path;
}

//---------------------------------------------------------
//Default Deconstructor
//---------------------------------------------------------
Text2D::~Text2D()
{
	fontSRV->Release();
	delete spriteBatch;
	delete spriteFontArial;
}

//---------------------------------------------------------
//Inititialize members
//---------------------------------------------------------
void Text2D::Init(ID3D11DeviceContext* context, ID3D11Device* device)
{
	// Set up 2D rendering stuff
	spriteBatch = new DirectX::SpriteBatch(context);
	spriteFontArial = new DirectX::SpriteFont(device, path);
}

void Text2D::SetText(const wchar_t* _text)
{
	textToDraw = _text;
}


//---------------------------------------------------------
//
//---------------------------------------------------------
void Text2D::SetupFont()
{
	spriteFontArial->GetSpriteSheet(&fontSRV);
}

void Text2D::DrawMyText()
{
	spriteBatch->Begin();
	spriteFontArial->DrawString(
		spriteBatch,
		L"This is some text, yo.",
		DirectX::XMFLOAT2(10, 120));
	spriteBatch->End();
}

//---------------------------------------------------------
//Return the font's SRV
//---------------------------------------------------------
ID3D11ShaderResourceView* Text2D::GetSRV()
{
	return fontSRV;
}