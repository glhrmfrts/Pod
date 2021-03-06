struct SectorList; struct Sector;

typedef struct // SectorList
{
	uint hasNamedFaces;
	uint num;
	Sector sectors(hasNamedFaces)[num] <optimize = false>;
} SectorList;

typedef struct(uint hasNamedFaces) // Sector
{
	Mesh mesh(hasNamedFaces, true);
	ubyte vertexGamma[mesh.numVertex]; // clamps to 0 - 127, 65 is normal gamma
	Vector3F16x16 boundingBoxMin; // z -= 2
	Vector3F16x16 boundingBoxMax; // z += 10
} Sector;
