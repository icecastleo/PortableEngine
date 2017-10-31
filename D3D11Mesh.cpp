
#include "D3D11Mesh.h"
#include "PC_IOSystem.h"
using namespace DirectX;

// --------------------------------------------------------
// Default Constructor
// --------------------------------------------------------
D3D11Mesh::D3D11Mesh() {}

// --------------------------------------------------------
// Constructor to load a file
// File read code provided by Chris Cascioli
// --------------------------------------------------------
//Mesh::Mesh(wchar_t* objFile, ID3D11Device *device, bool _hasNormalMap)
//{
//	//-------------------------------------------------------------------
//	//Change Later??
//	std::wstring path = L"Assets/Models/" + (std::wstring)objFile + L".obj";
//
//	// File input object
//	std::ifstream obj(path);
//	//-------------------------------------------------------------------
//
//	// Check for successful open
//	if (!obj.is_open())
//		return;
//
//	// Variables used while reading the file
//	std::vector<XMFLOAT3> positions;     // Positions from the file
//	std::vector<XMFLOAT3> normals;       // Normals from the file
//	std::vector<XMFLOAT2> uvs;           // UVs from the file
//	std::vector<Vertex> verts;           // Verts we're assembling
//	std::vector<UINT> indices;           // Indices of these verts
//	unsigned int vertCounter = 0;        // Count of vertices/indices
//	char chars[100];                     // String for line reading
//
//										 // Still have data left?
//	while (obj.good())
//	{
//		// Get the line (100 characters should be more than enough)
//		obj.getline(chars, 100);
//
//		// Check the type of line
//		if (chars[0] == 'v' && chars[1] == 'n')
//		{
//			// Read the 3 numbers directly into an XMFLOAT3
//			XMFLOAT3 norm;
//			sscanf_s(
//				chars,
//				"vn %f %f %f",
//				&norm.x, &norm.y, &norm.z);
//
//			// Add to the list of normals
//			normals.push_back(norm);
//		}
//		else if (chars[0] == 'v' && chars[1] == 't')
//		{
//			// Read the 2 numbers directly into an XMFLOAT2
//			XMFLOAT2 uv;
//			sscanf_s(
//				chars,
//				"vt %f %f",
//				&uv.x, &uv.y);
//
//			// Add to the list of uv's
//			uvs.push_back(uv);
//		}
//		else if (chars[0] == 'v')
//		{
//			// Read the 3 numbers directly into an XMFLOAT3
//			XMFLOAT3 pos;
//			sscanf_s(
//				chars,
//				"v %f %f %f",
//				&pos.x, &pos.y, &pos.z);
//
//			// Add to the positions
//			positions.push_back(pos);
//		}
//		else if (chars[0] == 'f')
//		{
//			// Read the face indices into an array
//			unsigned int i[12];
//			int facesRead = sscanf_s(
//				chars,
//				"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
//				&i[0], &i[1], &i[2],
//				&i[3], &i[4], &i[5],
//				&i[6], &i[7], &i[8],
//				&i[9], &i[10], &i[11]);
//
//			// - Create the verts by looking up
//			//    corresponding data from vectors
//			// - OBJ File indices are 1-based, so
//			//    they need to be adusted
//			Vertex v1;
//			v1.Position = positions[i[0] - 1];
//			v1.UV = uvs[i[1] - 1];
//			v1.Normal = normals[i[2] - 1];
//
//			Vertex v2;
//			v2.Position = positions[i[3] - 1];
//			v2.UV = uvs[i[4] - 1];
//			v2.Normal = normals[i[5] - 1];
//
//			Vertex v3;
//			v3.Position = positions[i[6] - 1];
//			v3.UV = uvs[i[7] - 1];
//			v3.Normal = normals[i[8] - 1];
//
//			// The model is most likely in a right-handed space,
//			// especially if it came from Maya.  We want to convert
//			// to a left-handed space for DirectX.  This means we 
//			// need to:
//			//  - Invert the Z position
//			//  - Invert the normal's Z
//			//  - Flip the winding order
//			// We also need to flip the UV coordinate since DirectX
//			// defines (0,0) as the top left of the texture, and many
//			// 3D modeling packages use the bottom left as (0,0)
//
//			// Flip the UV's since they're probably "upside down"
//			v1.UV.y = 1.0f - v1.UV.y;
//			v2.UV.y = 1.0f - v2.UV.y;
//			v3.UV.y = 1.0f - v3.UV.y;
//
//			// Flip Z (LH vs. RH)
//			v1.Position.z *= -1.0f;
//			v2.Position.z *= -1.0f;
//			v3.Position.z *= -1.0f;
//
//			// Flip normal Z
//			v1.Normal.z *= -1.0f;
//			v2.Normal.z *= -1.0f;
//			v3.Normal.z *= -1.0f;
//
//			// Add the verts to the vector (flipping the winding order)
//			verts.push_back(v1);
//			verts.push_back(v3);
//			verts.push_back(v2);
//
//			// Add three more indices
//			indices.push_back(vertCounter); vertCounter += 1;
//			indices.push_back(vertCounter); vertCounter += 1;
//			indices.push_back(vertCounter); vertCounter += 1;
//
//			// Was there a 4th face?
//			if (facesRead == 12)
//			{
//				// Make the last vertex
//				Vertex v4;
//				v4.Position = positions[i[9] - 1];
//				v4.UV = uvs[i[10] - 1];
//				v4.Normal = normals[i[11] - 1];
//
//				// Flip the UV, Z pos and normal
//				v4.UV.y = 1.0f - v4.UV.y;
//				v4.Position.z *= -1.0f;
//				v4.Normal.z *= -1.0f;
//
//				// Add a whole triangle (flipping the winding order)
//				verts.push_back(v1);
//				verts.push_back(v4);
//				verts.push_back(v3);
//
//				// Add three more indices
//				indices.push_back(vertCounter); vertCounter += 1;
//				indices.push_back(vertCounter); vertCounter += 1;
//				indices.push_back(vertCounter); vertCounter += 1;
//			}
//		}
//	}
//
//	// Close the file and create the actual buffers
//	obj.close();
//	// - At this point, "verts" is a vector of Vertex structs, and can be used
//	//    directly to create a vertex buffer:  &verts[0] is the address of the first vert
//	//
//	// - The vector "indices" is similar. It's a vector of unsigned ints and
//	//    can be used directly for the index buffer: &indices[0] is the address of the first int
//	//
//	// - "vertCounter" is BOTH the number of vertices and the number of indices
//	// - Yes, the indices are a bit redundant here (one per vertex)
//
//	indCount = vertCounter;
//	CreateGeometry(&verts[0], vertCounter, &indices[0], device);
//
//	vertexCollection = verts;
//	indexCollection = indices;
//	hasNormalMap = _hasNormalMap;
//}

// --------------------------------------------------------
// Constructor
// --------------------------------------------------------
D3D11Mesh::D3D11Mesh(wchar_t* objName, ID3D11Device *device, bool normalmap)
{

	PC_IOSystem::instance()->loadObj(objName);
	hasNormalMap = normalmap;
	// Initialize fields
	vertBuffer = 0;
	indBuffer = 0;

	indCount = PC_IOSystem::instance()->getindCount();
	vertexCollection = PC_IOSystem::instance()->getVertexFromObj();
	indexCollection = PC_IOSystem::instance()->getindixFromObj();


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
void D3D11Mesh::CreateGeometry(Vertex* verts, int numVerts, unsigned int *ind, ID3D11Device *device)
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

	device->CreateBuffer(&vbd, &initialVertexData, &vertBuffer);


	// Create the INDEX BUFFER description ------------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC ibd = {};
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * indCount;         // number of indices in the buffer
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
	device->CreateBuffer(&ibd, &initialIndexData, &indBuffer);

}

// --------------------------------------------------------
//Calculate the tangents of the vertices in a mesh
// --------------------------------------------------------
//void Mesh::CalculateTangents(Vertex* verts, int numVerts, size_t* indices, int numIndices)
void D3D11Mesh::CalculateTangents(Vertex* verts, int numVerts, unsigned int* indices, int numIndices)
{
	// Reset tangents
	for (int i = 0; i < numVerts; i++)
	{
		verts[i].Tangent = glm::vec3(0, 0, 0);
	}

	// Calculate tangents one whole triangle at a time
	for (int i = 0; i < numVerts;)
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
int D3D11Mesh::GetIndexCount()
{
	return indCount;
}

std::vector<Vertex> D3D11Mesh::GetVertexCollection()
{
	return vertexCollection;
}
std::vector<UINT> D3D11Mesh::GetIndexCollection()
//std::vector<size_t> Mesh::GetIndexCollection()
{
	return indexCollection;
}