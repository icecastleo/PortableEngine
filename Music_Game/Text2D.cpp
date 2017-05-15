#include "Tex2Dt.h"

//---------------------------------------------------------
//Default Constructor using Arial as the default font
//---------------------------------------------------------
Text2D::Text2D()
{
	textList = std::vector<textObject>();
	path = L"Assets/fonts/Arial.spritefont";
}

//---------------------------------------------------------
//Constructor taking a font file path
//---------------------------------------------------------
Text2D::Text2D(const wchar_t* _path)
{
	textList = std::vector<textObject>();
	path = _path;
}

//---------------------------------------------------------
//Default Deconstructor
//---------------------------------------------------------
Text2D::~Text2D()
{
	//fontSRV->Release();
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
//Setup the font
//---------------------------------------------------------
void Text2D::SetupFont()
{
	spriteFontArial->GetSpriteSheet(&fontSRV);
}

//---------------------------------------------------------
//Draw the list of text objects
//---------------------------------------------------------
void Text2D::DrawMyText()
{
	//Begin the sprite batch drawing
	spriteBatch->Begin();

	//loop through the different items to draw
	if (textList.size() > 0)
	{
		for (int t = 0; t < textList.size(); t++)
		{
			spriteFontArial->DrawString(
				spriteBatch,
				textList.at(t).text,
				textList.at(t).positon);
		}
	}
	//end drawing
	spriteBatch->End();
}

//---------------------------------------------------------
//Draw the list of text objects
//---------------------------------------------------------
void Text2D::DrawLiveText(const wchar_t* text, DirectX::XMFLOAT2 pos)
{
	//Begin the sprite batch drawing
	spriteBatch->Begin();

	spriteFontArial->DrawString(
		spriteBatch,
		text,
		pos);

	//end drawing
	spriteBatch->End();
}

//---------------------------------------------------------
//Add a text object to be drawn
//---------------------------------------------------------
void Text2D::AddText(const wchar_t* _text, DirectX::XMFLOAT2 _pos)
{
	textObject temp;
	temp.text = _text;
	temp.positon = _pos;
	textList.push_back(temp);
}

//---------------------------------------------------------
//Clear the text list
//---------------------------------------------------------
void Text2D::ClearText()
{
	if (textList.size() > 0)
	{
		textList.clear();
	}
}

//---------------------------------------------------------
//Return the font's SRV
//---------------------------------------------------------
ID3D11ShaderResourceView* Text2D::GetSRV()
{
	return fontSRV;
}