// ==== Primitive Types ================================================================================================

typedef ubyte bool <read = boolRead>;
string boolRead(bool& value)
{
	return value ? "true" : "false";
}
local bool true <hidden = true> = 1;
local bool false <hidden = true> = 0;

typedef union // Dword
{
	int i;
	float f;
} Dword <read = DwordRead>;
string DwordRead(Dword& v)
{
	string s;
	SPrintf(s, "%d / %f", v.i, v.f);
	return s;
}

typedef int fixed16x16 <read = fixed16x16Read, write = fixed16x16Write>;
string fixed16x16Read(fixed16x16& value)
{
	string s;
	SPrintf(s, "%f", value / (float)(1 << 16));
	return s;
}
void fixed16x16Write(fixed16x16& value, string s)
{
	float f;
	SScanf(s, "%f", f);
	value = f * (1 << 16);
}

// ==== Matrices =======================================================================================================

typedef struct // Matrix2x2
{
	float m11; float m12;
	float m21; float m22;
} Matrix2x2 <read = Matrix2x2Read, write = Matrix2x2Write>;
string Matrix2x2Read(Matrix2x2& v)
{
	string s;
	SPrintf(s, "((%f, %f), (%f, %f))",
		v.m11, v.m12,
		v.m21, v.m22);
	return s;
}
void Matrix2x2Write(Matrix2x2& v, string s)
{
	SScanf(s, "((%f, %f), (%f, %f))",
		v.m11, v.m12,
		v.m21, v.m22);
}

typedef struct // Matrix2x3
{
	float m11; float m12; float m13;
	float m21; float m22; float m23;
} Matrix2x3 <read = Matrix2x3Read, write = Matrix2x3Write>;
string Matrix2x3Read(Matrix2x3& v)
{
	string s;
	SPrintf(s, "((%f, %f, %f), (%f, %f, %f))",
		v.m11, v.m12, v.m13,
		v.m21, v.m22, v.m23);
	return s;
}
void Matrix2x3Write(Matrix2x3& v, string s)
{
	SScanf(s, "((%f, %f, %f), (%f, %f, %f))",
		v.m11, v.m12, v.m13,
		v.m21, v.m22, v.m23);
}

typedef struct // Matrix2x4
{
	float m11; float m12; float m13; float m14;
	float m21; float m22; float m23; float m24;
} Matrix2x4 <read = Matrix2x4Read, write = Matrix2x4Write>;
string Matrix2x4Read(Matrix2x4& v)
{
	string s;
	SPrintf(s, "((%f, %f, %f, %f), (%f, %f, %f, %f))",
		v.m11, v.m12, v.m13, v.m14,
		v.m21, v.m22, v.m23, v.m24);
	return s;
}
void Matrix2x4Write(Matrix2x4& v, string s)
{
	SScanf(s, "((%f, %f, %f, %f), (%f, %f, %f, %f))",
		v.m11, v.m12, v.m13, v.m14,
		v.m21, v.m22, v.m23, v.m24);
}

typedef struct // Matrix3x2
{
	float m11; float m12;
	float m21; float m22;
	float m31; float m32;
} Matrix3x2 <read = Matrix3x2Read, write = Matrix3x2Write>;
string Matrix3x2Read(Matrix3x2& v)
{
	string s;
	SPrintf(s, "((%f, %f), (%f, %f), (%f, %f))",
		v.m11, v.m12,
		v.m21, v.m22,
		v.m31, v.m31);
	return s;
}
void Matrix3x2Write(Matrix3x2& v, string s)
{
	SScanf(s, "((%f, %f), (%f, %f), (%f, %f))",
		v.m11, v.m12,
		v.m21, v.m22,
		v.m31, v.m31);
}

typedef struct // Matrix3x3
{
	float m11; float m12; float m13;
	float m21; float m22; float m23;
	float m31; float m32; float m33;
} Matrix3x3 <read = Matrix3x3Read, write = Matrix3x3Write>;
string Matrix3x3Read(Matrix3x3& v)
{
	string s;
	SPrintf(s, "((%f, %f, %f), (%f, %f, %f), (%f, %f, %f))",
		v.m11, v.m12, v.m13,
		v.m21, v.m22, v.m23,
		v.m31, v.m32, v.m33);
	return s;
}
void Matrix3x3Write(Matrix3x3& v, string s)
{
	SScanf(s, "((%f, %f, %f), (%f, %f, %f), (%f, %f, %f))",
		v.m11, v.m12, v.m13,
		v.m21, v.m22, v.m23,
		v.m31, v.m32, v.m33);
}

typedef struct // Matrix3x3F16x16
{
	fixed16x16 m11; fixed16x16 m12; fixed16x16 m13;
	fixed16x16 m21; fixed16x16 m22; fixed16x16 m23;
	fixed16x16 m31; fixed16x16 m32; fixed16x16 m33;
} Matrix3x3F16x16 <read = Matrix3x3F16x16Read>;
string Matrix3x3F16x16Read(Matrix3x3F16x16& v)
{
	string s;
	SPrintf(s, "((%s, %s, %s), (%s, %s, %s), (%s, %s, %s))",
		fixed16x16Read(v.m11), fixed16x16Read(v.m12), fixed16x16Read(v.m13),
		fixed16x16Read(v.m21), fixed16x16Read(v.m22), fixed16x16Read(v.m23),
		fixed16x16Read(v.m31), fixed16x16Read(v.m32), fixed16x16Read(v.m33));
	return s;
}

typedef struct // Matrix3x4
{
	float m11; float m12; float m13; float m14;
	float m21; float m22; float m23; float m24;
	float m31; float m32; float m33; float m34;
} Matrix3x4 <read = Matrix3x4Read, write = Matrix3x4Write>;
string Matrix3x4Read(Matrix3x4& v)
{
	string s;
	SPrintf(s, "((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
		v.m11, v.m12, v.m13, v.m14,
		v.m21, v.m22, v.m23, v.m24,
		v.m31, v.m32, v.m33, v.m34);
	return s;
}
void Matrix3x4Write(Matrix3x4& v, string s)
{
	SScanf(s, "((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
		v.m11, v.m12, v.m13, v.m14,
		v.m21, v.m22, v.m23, v.m24,
		v.m31, v.m32, v.m33, v.m34);
}

typedef struct // Matrix4x2
{
	float m11; float m12;
	float m21; float m22;
	float m31; float m32;
	float m41; float m42;
} Matrix4x2 <read = Matrix4x2Read, write = Matrix4x2Write>;
string Matrix4x2Read(Matrix4x2& v)
{
	string s;
	SPrintf(s, "((%f, %f), (%f, %f), (%f, %f), (%f, %f))",
		v.m11, v.m12,
		v.m21, v.m22,
		v.m31, v.m32,
		v.m41, v.m42);
	return s;
}
void Matrix4x2Write(Matrix4x2& v, string s)
{
	SScanf(s, "((%f, %f), (%f, %f), (%f, %f), (%f, %f))",
		v.m11, v.m12,
		v.m21, v.m22,
		v.m31, v.m32,
		v.m41, v.m42);
}

typedef struct // Matrix4x3
{
	float m11; float m12; float m13;
	float m21; float m22; float m23;
	float m31; float m32; float m33;
	float m41; float m42; float m43;
} Matrix4x3 <read = Matrix4x3Read, write = Matrix4x3Write>;
string Matrix4x3Read(Matrix4x3& v)
{
	string s;
	SPrintf(s, "((%f, %f, %f), (%f, %f, %f), (%f, %f, %f), (%f, %f, %f))",
		v.m11, v.m12, v.m13,
		v.m21, v.m22, v.m23,
		v.m31, v.m32, v.m33,
		v.m41, v.m42, v.m43);
	return s;
}
void Matrix4x3Write(Matrix4x3& v, string s)
{
	SScanf(s, "((%f, %f, %f), (%f, %f, %f), (%f, %f, %f), (%f, %f, %f))",
		v.m11, v.m12, v.m13,
		v.m21, v.m22, v.m23,
		v.m31, v.m32, v.m33,
		v.m41, v.m42, v.m43);
}

typedef struct // Matrix4x4
{
	float m11; float m12; float m13; float m14;
	float m21; float m22; float m23; float m24;
	float m31; float m32; float m33; float m34;
	float m41; float m42; float m43; float m44;
} Matrix4x4 <read = Matrix4x4Read, write = Matrix4x4Write>;
string Matrix4x4Read(Matrix4x4& v)
{
	string s;
	SPrintf(s, "((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
		v.m11, v.m12, v.m13, v.m14,
		v.m21, v.m22, v.m23, v.m24,
		v.m31, v.m32, v.m33, v.m34,
		v.m41, v.m42, v.m43, v.m44);
	return s;
}
void Matrix4x4Write(Matrix4x4& v, string s)
{
	SScanf(s, "((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
		v.m11, v.m12, v.m13, v.m14,
		v.m21, v.m22, v.m23, v.m24,
		v.m31, v.m32, v.m33, v.m34,
		v.m41, v.m42, v.m43, v.m44);
}

// ==== 2-dimensional vectors ==========================================================================================

typedef struct // Vector2
{
	float x; float y;
} Vector2 <read = Vector2Read, write = Vector2Write>;
string Vector2Read(Vector2& v)
{
	string s;
	SPrintf(s, "(%f, %f)", v.x, v.y);
	return s;
}
void Vector2Write(Vector2& v, string s)
{
	SScanf(s, "(%f, %f)", v.x, v.y);
}

typedef struct // Vector2B
{
	byte x; byte y;
} Vector2B <read = Vector2BRead, write = Vector2BWrite>;
string Vector2BRead(Vector2B& v)
{
	string s;
	SPrintf(s, "(%u, %u)", v.x, v.y);
	return s;
}
void Vector2BWrite(Vector2B& v, string s)
{
	SScanf(s, "(%u, %u)", v.x, v.y);
}

typedef struct // Vector2I
{
	int x; int y;
} Vector2I <read = Vector2IRead, write = Vector2IWrite>;
string Vector2IRead(Vector2& v)
{
	string s;
	SPrintf(s, "(%d, %d)", v.x, v.y);
	return s;
}
void Vector2IWrite(Vector2I& v, string s)
{
	SScanf(s, "(%d, %d)", v.x, v.y);
}

typedef struct // Vector2U
{
	uint x; uint y;
} Vector2U <read = Vector2URead, write = Vector2UWrite>;
string Vector2URead(Vector2U& v)
{
	string s;
	SPrintf(s, "(%u, %u)", v.x, v.y);
	return s;
}
void Vector2UWrite(Vector2& v, string s)
{
	SScanf(s, "(%u, %u)", v.x, v.y);
}

// ==== 3-dimensional vectors ==========================================================================================

typedef struct // Vector3
{
	float x; float y; float z;
} Vector3 <read = Vector3Read, write = Vector3Write>;
string Vector3Read(Vector3& v)
{
	string s;
	SPrintf(s, "(%f, %f, %f)", v.x, v.y, v.z);
	return s;
}
void Vector3Write(Vector3& v, string s)
{
	SScanf(s, "(%f, %f, %f)", v.x, v, y, v.z);
}

typedef struct // Vector3B
{
	byte x; byte y; byte z;
} Vector3B <read = Vector3BRead, write = Vector3BWrite>;
string Vector3BRead(Vector3B& v)
{
	string s;
	SPrintf(s, "(%u, %u, %u)", v.x, v.y, v.z);
	return s;
}
void Vector3BWrite(Vector3B& v, string s)
{
	SScanf(s, "(%u, %u, %u)", v.x, v, y, v.z);
}

typedef struct // Vector3F16x16
{
	fixed16x16 x; fixed16x16 y; fixed16x16 z;
} Vector3F16x16 <read = Vector3F16x16Read>;
string Vector3F16x16Read(Vector3F16x16& v)
{
	string s;
	SPrintf(s, "(%s, %s, %s)", fixed16x16Read(v.x), fixed16x16Read(v.y), fixed16x16Read(v.z));
	return s;
}

typedef struct // Vector3
{
	int x; int y; int z;
} Vector3I <read = Vector3IRead, write = Vector3IWrite>;
string Vector3IRead(Vector3I& v)
{
	string s;
	SPrintf(s, "(%d, %d, %d)", v.x, v.y, v.z);
	return s;
}
void Vector3IWrite(Vector3I& v, string s)
{
	SScanf(s, "(%d, %d, %d)", v.x, v, y, v.z);
}

typedef struct // Vector3U
{
	uint x; uint y; uint z;
} Vector3U <read = Vector3URead, write = Vector3UWrite>;
string Vector3URead(Vector3U& v)
{
	string s;
	SPrintf(s, "(%u, %u, %u)", v.x, v.y, v.z);
	return s;
}
void Vector3UWrite(Vector3U& v, string s)
{
	SScanf(s, "(%u, %u, %u)", v.x, v, y, v.z);
}

// ==== 4-dimensional vectors ==========================================================================================

typedef struct // Vector4
{
	float x; float y; float z; float w;
} Vector4 <read = Vector4Read, write = Vector4Write>;
string Vector4Read(Vector4& v)
{
	string s;
	SPrintf(s, "(%f, %f, %f, %f)", v.x, v.y, v.z, v.w);
	return s;
}
void Vector4Write(Vector4& v, string s)
{
	SScanf(s, "(%f, %f, %f, %f)", v.x, v.y, v.z, v.w);
}

typedef struct // Vector4B
{
	byte x; byte y; byte z; byte w;
} Vector4B <read = Vector4BRead, write = Vector4BWrite>;
string Vector4BRead(Vector4B& v)
{
	string s;
	SPrintf(s, "(%u, %u, %u, %u)", v.x, v.y, v.z, v.w);
	return s;
}
void Vector4BWrite(Vector4B& v, string s)
{
	SScanf(s, "(%u, %u, %u, %u)", v.x, v.y, v.z, v.w);
}

typedef struct // Vector4
{
	int x; int y; int z; int w;
} Vector4I <read = Vector4IRead, write = Vector4IWrite>;
string Vector4IRead(Vector4I& v)
{
	string s;
	SPrintf(s, "(%d, %d, %d, %d)", v.x, v.y, v.z, v.w);
	return s;
}
void Vector4IWrite(Vector4I& v, string s)
{
	SScanf(s, "(%d, %d, %d, %d)", v.x, v.y, v.z, v.w);
}

typedef struct // Vector4U
{
	uint x; uint y; uint z; uint w;
} Vector4U <read = Vector4URead, write = Vector4UWrite>;
string Vector4URead(Vector4U& v)
{
	string s;
	SPrintf(s, "(%u, %u, %u, %u)", v.x, v.y, v.z, v.w);
	return s;
}
void Vector4UWrite(Vector4U& v, string s)
{
	SScanf(s, "(%u, %u, %u, %u)", v.x, v.y, v.z, v.w);
}

// ==== Methods ========================================================================================================

void FAlign(byte alignment)
{
	local int bytesToSkip <hidden = true> = (-FTell() % alignment + alignment) % alignment;
	while (bytesToSkip--)
	{
		byte padding <fgcolor = 0x808080, hidden = true>;
	}
}

void FPad(int count)
{
	while (count--)
	{
		byte padding <fgcolor = 0x808080, hidden = true>;
	}
}
