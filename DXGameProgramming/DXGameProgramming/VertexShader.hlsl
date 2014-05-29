// VertexShader.hlsl  

// The GPU version of the constant buffer
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};  

// The input vertices 
struct VertexShaderInput
{ 
	float3 position :
	POSITION; 
	float3 normal : NORMAL0;
	float2 tex : TEXCOORD0;

	//float3 color : COLOR0; 
};  

// The output vertices as the pixel shader will get them 
struct VertexShaderOutput 
{  
	float4 position : SV_POSITION; 
	float3 normal : NORMAL0;
    float2 tex : TEXCOORD0;

	//float3 color : COLOR0;
};

// This is the main entry point to the shader: 
VertexShaderOutput main(VertexShaderInput input) 
{ 
	VertexShaderOutput output; 
	float4 pos = float4(input.position, 1.0f); 

 // Use constant buffer matrices to position the vertices: 
 pos = mul(pos, model); // Position the model in the world
 pos = mul(pos, view); // Position the world with respect to a camera  
 pos = mul(pos, projection);// Project the vertices  
 output.position = pos;  
 
 // Pass the texture coordinates unchanged to pixel shader
 output.tex = input.tex;

 
 // Pass the normals unchanged to the pixel shader
 output.normal = input.normal;


 // Pass the color of the vertices to the pixel shader 
 //output.color = input.color;  
 return output; 

} 