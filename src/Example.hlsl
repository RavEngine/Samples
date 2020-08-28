// HLSL shader version 4.0 (for Direct3D 11/ 12)

static float4x4 wvpMatrix = {
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1 }
};
//cbuffer Settings : register(b0) {
//	
//};

struct InputVS
{
	float3 position : POSITION;
	float3 color : COLOR;
};

struct OutputVS
{
	float4 position : SV_Position;
	float3 color : COLOR;
};

// Vertex shader main function
OutputVS VS(InputVS inp)
{
	OutputVS outp;
	outp.position = mul(wvpMatrix,float4(inp.position, 1));
	outp.color = inp.color;
	return outp;
}

// Pixel shader main function
float4 PS(OutputVS inp) : SV_Target
{
	return float4(inp.color, 1);
};