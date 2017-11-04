
#include "D3D11Mesh.h"
#include "PC_IOSystem.h"

D3D11Mesh::D3D11Mesh(wchar_t* objName, ID3D11Device *device, bool normalmap)
{
	wstring path = L"Assets/Models/" + (wstring)objName + L".obj";

	const wchar_t *src = path.c_str(); 
	
	size_t size = wcslen(src) * 2 + 2; 
	
	char *cPath = new char[size]; 
	
	size_t ret; 
	
	// success
	assert(wcstombs_s(&ret, cPath, size, src, size) == 0);

	PC_IOSystem::instance()->loadObj(cPath);

	delete cPath;

	hasNormalMap = normalmap;
	// Initialize fields
	vertBuffer = 0;
	indBuffer = 0;

	indCount = PC_IOSystem::instance()->getIndCount();
	vertexCollection = PC_IOSystem::instance()->getVertexFromObj();
	indexCollection = PC_IOSystem::instance()->getIndicesFromObj();

	CreateGeometry(&vertexCollection[0], indCount, &indexCollection[0], device);
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
	if (vertBuffer) { vertBuffer->Release(); }
	if (indBuffer) { indBuffer->Release(); }
}


// --------------------------------------------------------
//Creates the geometry we're going to draw
//Copied from Game.cpp - Chris Cascioli
//Modified for use here
// --------------------------------------------------------
void D3D11Mesh::CreateGeometry(Vertex* verts, uint16_t numVerts, uint16_t *ind, ID3D11Device *device)
//void Mesh::CreateGeometry(Vertex* verts, int numVerts, size_t *ind, ID3D11Device *device)
{
	//If the model has a normal map, calculate the tangents
	if (hasNormalMap)
	{
		CalculateTangents(verts, numVerts, ind, numVerts);
	}

	// Create the VERTEX BUFFER description -----------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC vbd = {};
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * numVerts;	// number of vertices in the buffer
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Tells DirectX this is a vertex buffer
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	// Create the proper struct to hold the initial vertex data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialVertexData = {};
	initialVertexData.pSysMem = verts;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	HRESULT result = device->CreateBuffer(&vbd, &initialVertexData, &vertBuffer);


	// Create the INDEX BUFFER description ------------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC ibd = {};
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(uint16_t) * numVerts;         // number of indices in the buffer
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; // Tells DirectX this is an index buffer
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	// Create the proper struct to hold the initial index data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialIndexData = {};
	initialIndexData.pSysMem = ind;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	result = device->CreateBuffer(&ibd, &initialIndexData, &indBuffer);
}

// --------------------------------------------------------
//Calculate the tangents of the vertices in a mesh
// --------------------------------------------------------
//void Mesh::CalculateTangents(Vertex* verts, int numVerts, size_t* indices, int numIndices)
void D3D11Mesh::CalculateTangents(Vertex* verts, uint16_t numVerts, uint16_t* indices, uint16_t numIndices)
{
	// Reset tangents
	for (size_t i = 0; i < numVerts; i++)
	{
		verts[i].Tangent = glm::vec3(0, 0, 0);
	}

	// Calculate tangents one whole triangle at a time
	for (size_t i = 0; i < numVerts;)
	{
		// Grab indices and vertices of first triangle
		size_t i1 = indices[i++];
		size_t i2 = indices[i++];
		size_t i3 = indices[i++];
		Vertex* v1 = &verts[i1];
		Vertex* v2 = &verts[i2];
		Vertex* v3 = &verts[i3];

		// Calculate vectors relative to triangle positions
		float x1 = v2->Position.x - v1->Position.x;
		float y1 = v2->Position.y - v1->Position.y;
		float z1 = v2->Position.z - v1->Position.z;

		float x2 = v3->Position.x - v1->Position.x;
		float y2 = v3->Position.y - v1->Position.y;
		float z2 = v3->Position.z - v1->Position.z;

		// Do the same for vectors relative to triangle uv's
		float s1 = v2->UV.x - v1->UV.x;
		float t1 = v2->UV.y - v1->UV.y;

		float s2 = v3->UV.x - v1->UV.x;
		float t2 = v3->UV.y - v1->UV.y;

		// Create vectors for tangent calculation
		float r = 1.0f / (s1 * t2 - s2 * t1);

		float tx = (t2 * x1 - t1 * x2) * r;
		float ty = (t2 * y1 - t1 * y2) * r;
		float tz = (t2 * z1 - t1 * z2) * r;

		// Adjust tangents of each vert of the triangle
		v1->Tangent.x += tx;
		v1->Tangent.y += ty;
		v1->Tangent.z += tz;

		v2->Tangent.x += tx;
		v2->Tangent.y += ty;
		v2->Tangent.z += tz;

		v3->Tangent.x += tx;
		v3->Tangent.y += ty;
		v3->Tangent.z += tz;
	}

	// Ensure all of the tangents are orthogonal to the normals
	for (int i = 0; i < numVerts; i++)
	{
		// Grab the two vectors
		//XMVECTOR normal = XMLoadFloat3(&verts[i].Normal);
		//XMVECTOR tangent = XMLoadFloat3(&verts[i].Tangent);

		glm::vec3 normal = verts[i].Normal;
		glm::vec3 tangent = verts[i].Tangent;

		// Use Gram-Schmidt orthogonalize
		//tangent = XMVector3Normalize(tangent - normal * XMVector3Dot(normal, tangent));

		tangent = glm::normalize(
			tangent - normal * glm::dot(normal, tangent)); 

		// Store the tangent
		//XMStoreFloat3(&verts[i].Tangent, tangent);
		verts[i].Tangent = tangent;

	}
}

// --------------------------------------------------------
//Returns a pointer to a vertex buffer.
// --------------------------------------------------------
ID3D11Buffer* D3D11Mesh::GetVertexBuffer()
{
	return vertBuffer;
}

// --------------------------------------------------------
//Returns a pointer to an index buffer.
// --------------------------------------------------------
ID3D11Buffer* D3D11Mesh::GetIndexBuffer()
{
	return indBuffer;
}

// --------------------------------------------------------
//Returns the number of indices for this mesh.
// --------------------------------------------------------
size_t D3D11Mesh::GetIndexCount()
{
	return indCount;
}

std::vector<Vertex> D3D11Mesh::GetVertexCollection()
{
	return vertexCollection;
}
std::vector<uint16_t> D3D11Mesh::GetIndexCollection()
{
	return indexCollection;
}