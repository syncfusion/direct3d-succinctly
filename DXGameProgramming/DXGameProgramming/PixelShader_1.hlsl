// PixelShader.hlsl  

// Input is exactly the same as 
// vertex shader output!

struct PixelShaderInput 
{  
	float4 position : SV_POSITION;  
	float3 color : COLOR0; 
};  

// Main entry point to the shader 

float4 main(PixelShaderInput input) : SV_TARGET
{  
	// Return the color unchanged
	return float4(input.color,1.0f);
}