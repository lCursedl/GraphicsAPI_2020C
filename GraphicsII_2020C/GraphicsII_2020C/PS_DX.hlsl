//--------------------------------------------------------------------------------------
// File: Tutorial07_2.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

Texture2D txDiffuse : register ( t0 );
SamplerState samp : register ( s0 );

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix Projection;	
    float4 vMeshColor;
};
//--------------------------------------------------------------------------------------
struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
	float3 wsPos : TEXCOORD1;
};
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main( PS_INPUT input) : SV_Target
{
    return txDiffuse.Sample(samp, input.Tex);
}