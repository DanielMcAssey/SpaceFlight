void main_vp(

    // IN
	float4 iPosition	        : POSITION,
	float3 i3DCoord             : TEXCOORD0,
	float2 iNoiseUV             : TEXCOORD1,
	float  iOpacity             : TEXCOORD2,
	
	// OUT
	out float4 oPosition		: POSITION,
	out float3 o3DCoord         : TEXCOORD0,
	out float2 oNoiseUV         : TEXCOORD1,
	out float  oOpacity         : TEXCOORD2,
	out float3 oEyePixel        : TEXCOORD3,
	out float  oDistance        : TEXCOORD4,
	
	// UNIFORM
	uniform float4x4 uWorldViewProj,
	uniform float3   uCameraPosition,
	uniform float    uRadius)
{
	oPosition   = mul(uWorldViewProj, iPosition);
	o3DCoord = i3DCoord;
    oNoiseUV = iNoiseUV;
    oOpacity = iOpacity;
    oEyePixel = normalize(iPosition.xyz - uCameraPosition);
    oDistance = length(float2(iPosition.x, iPosition.z)) / uRadius;
}

void main_fp(

    // IN
    float3 i3DCoord  : TEXCOORD0,
    float2 iNoiseUV  : TEXCOORD1,
    float  iOpacity  : TEXCOORD2,
    float3 iEyePixel : TEXCOORD3,
    float  iDistance : TEXCOORD4,
	
	// OUT 
	out float4 oColour		: Colour,
	
	// UNIFORM
	uniform float     uInterpolation,
	uniform float3    uSunDirection,
	uniform float3    uAmbientColour,
	uniform float3    uSunColour,
	uniform float4    uLightResponse,
	uniform float4    uAmbientFactors,
	uniform sampler3D uDensity0 : register(s0),
	uniform sampler3D uDensity1 : register(s1),
	uniform sampler2D uNoise    : register(s2))
{    
	float3 Noise = tex2D(uNoise, iNoiseUV*5);
	float3 Final3DCoord = i3DCoord+0.002575*(Noise-0.5f)*2;
	Final3DCoord.z = saturate(Final3DCoord.z);
	float3 Density0 = tex3D(uDensity0, Final3DCoord);
	float3 Density1 = tex3D(uDensity1, Final3DCoord);
	float3 Density  = Density0*(1-uInterpolation) + Density1*uInterpolation;
	float3 finalColour = float3(0,0,0);
	float  Opacity    = 0;

	if (Density.x > 0)
	{
	    float cos0 = saturate(dot(uSunDirection,iEyePixel));
	    float c2=cos0*cos0;
		float Beta = c2*uLightResponse.y*(0.5f+2.5f*saturate(1-2*uSunDirection.y)*Density.y);
		float sunaccumulation = max(0.2, saturate(Beta+Density.y*uLightResponse.x+pow(iDistance,1.5)*uLightResponse.w));
		float ambientaccumulation = saturate(uAmbientFactors.x + uAmbientFactors.y*i3DCoord.z + uAmbientFactors.z*pow(i3DCoord.z,2) + uAmbientFactors.w*pow(i3DCoord.z,3))*uLightResponse.z;
		finalColour = uAmbientColour*ambientaccumulation + uSunColour*sunaccumulation;
		Opacity = (1 - exp(-Density.x*(7.5-6.5*i3DCoord.z)))*iOpacity;
	}
	
    oColour = float4(finalColour, Opacity);
}