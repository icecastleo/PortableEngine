
#include "D3D11Mesh.h"

D3D11Mesh::D3D11Mesh(char* path, ID3D11Device *device)
	:Mesh(path)
{
	CreateGeometry(&verts[0], verts.size(), &indices[0], indices.size(), device);
}


// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//Copied from Game.cpp - Chris Cascioli
//Modified for use here
// --------------------------------------------------------
D3D11Mesh::~D3D11Mesh()
{
	// Release any (and all!) DirectX objects
	if (vertBuffer) { static_cast<ID3D11Buffer*>(vertBuffer)->Release(); }
	if (indBuffer) { static_cast<ID3D11Buffer*>(indBuffer)->Release(); }
}


// --------------------------------------------------------
//Creates the geometry we're going to draw
//Copied from Game.cpp - Chris Cascioli
//Modified for use here
// --------------------------------------------------------
void D3D11Mesh::CreateGeometry(Vertex* verts, size_t vertexCount, uint16_t *ind, size_t indexCount, ID3D11Device *device)
{
	// Create the VERTEX BUFFER description -----------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC vbd = {};
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * vertexCount;	// number of vertices in the buffer
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// Tells DirectX this is a vertex buffer
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	// Create the proper struct to hold the initial vertex data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialVertexData = {};
	initialVertexData.pSysMem = verts;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	ID3D11Buffer *temp = 0;
	HRESULT result = device->CreateBuffer(&vbd, &initialVertexData, &temp);
	vertBuffer = temp;

	// Create the INDEX BUFFER description ------------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC ibd = {};
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(uint16_t) * indexCount;	// number of indices in the buffer
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;		// Tells DirectX this is an index buffer
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	// Create the proper struct to hold the initial index data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialIndexData = {};
	initialIndexData.pSysMem = ind;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	temp = 0;
	result = device->CreateBuffer(&ibd, &initialIndexData, &temp);
	indBuffer = temp;
}