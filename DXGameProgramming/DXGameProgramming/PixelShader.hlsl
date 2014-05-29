// PixelShader.hlsl  
Texture2D shaderTexture; // This is the texture
SamplerState samplerState;

// Input is exactly the same as 
// vertex shader output! 
struct PixelShaderInput 
{ 
	float4 position : SV_POSITION; 
	//float3 color : COLOR0;
	float3 normal : NORMAL0;

	float2 tex: TEXCOORD0;

};  

// Main entry point to the shader 
float4 main(PixelShaderInput input) : SV_TARGET 
{  
 //float4 emissive = float4(0.2f, 0.2f, 0.2f, 1.0f);
 float4 emissive = float4(0.0f, 0.0f, 0.0f, 1.0f);
 //float materialReflection = 1.0f;
 float materialReflection = 9.0f;
 float4 ambientLightColor = float4(0.1f, 0.1f, 0.1f, 1.0f);
 float4 ambient = ambientLightColor * materialReflection;
  
 //float diffuseIntensity = 1.0f;
 float diffuseIntensity = 9.0f;
 float4 diffuseLightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
 //float4 diffuseLightDirection = float4(1.0f, -1.0f, 1.0f, 1.0f);
 float4 diffuseLightDirection = float4(-1.0f, -1.0f, -1.0f, 1.0f);
 float4 materialColor = shaderTexture.Sample(samplerState,input.tex);
 float4 diffuse = diffuseIntensity * diffuseLightColor * saturate(dot(-diffuseLightDirection, input.normal)); 
 diffuse = diffuse * materialColor;

 
 float4 finalColor = emissive + ambient + diffuse;

 finalColor = normalize(finalColor);
 
 return finalColor; 

	 //float4 textureColor = shaderTexture.Sample(samplerState, input.tex); 
	
	
 // Return the color unchanged
 //return textureColor;

	// Return the color unchanged  
	//return float4(input.color,1.0f); 
}