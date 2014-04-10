float scale(float cos, float uScaleDepth)
{
	float x = 1.0 - cos;
	return uScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

void main_vp(
    // IN
	float4 iPosition	        : POSITION,
	float3 iNPosition           : TEXCOORD0,
	float2 iUV                  : TEXCOORD1,
	float  iOpacity             : TEXCOORD2,
	
	// OUT
	out float4 oPosition		: POSITION,
	out float2 oUV              : TEXCOORD0,
	out float3 oRayleighColor   : TEXCOORD1,
	out float3 oMieColor        : TEXCOORD2,
	out float3 oDirection       : TEXCOORD3,
	out float  oOpacity         : TEXCOORD4,
	out float  oHeight          : TEXCOORD5,
	
	// UNIFORM
	uniform float4x4 uWorldViewProj,
	
	// Global information
	uniform float3 uLightDir,
	
	// Position information
	uniform float3 uCameraPos,
	uniform float3 uInvWaveLength,
	uniform float  uInnerRadius,
	
	// Scattering parameters
	uniform float  uKrESun, // Kr * ESun
	uniform float  uKmESun, // Km * ESun
	uniform float  uKr4PI,  // Kr * 4 * PI
	uniform float  uKm4PI,  // Km * 4 * PI
	
	// Atmosphere properties
	uniform float uScale,
	uniform float uScaleDepth,
	uniform float uScaleOverScaleDepth,
	
	// Number of samples
	uniform int   uNumberOfSamples,
	uniform float uSamples)
{
	oPosition   = mul(uWorldViewProj, iPosition);
	float3 v3Pos = iNPosition;
	v3Pos.y += uInnerRadius;
    float3 v3Ray = v3Pos - uCameraPos;
	float fFar = length(v3Ray);
	v3Ray /= fFar;
	float3 v3Start = uCameraPos;
	float fHeight = uCameraPos.y;
	float fStartAngle = dot(v3Ray, v3Start) / fHeight;
	float fDepth = exp(uScaleOverScaleDepth * (uInnerRadius - uCameraPos.y));
	float fStartOffset = fDepth * scale(fStartAngle, uScaleDepth);
	float fSampleLength = fFar / uSamples;
	float fScaledLength = fSampleLength * uScale;
	float3 v3SampleRay = v3Ray * fSampleLength;
	float3 v3SamplePoint = v3Start + v3SampleRay * 0.5f;
	float3 color = float3(0,0,0);
	
	for (int i = 0; i < uNumberOfSamples; i++)
	{
		float fHeight = length(v3SamplePoint);
		float fDepth = exp(uScaleOverScaleDepth * (uInnerRadius-fHeight));
		float fLightAngle = dot(uLightDir, v3SamplePoint) / fHeight;
		float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight;
		float fScatter = (fStartOffset + fDepth*(scale(fLightAngle, uScaleDepth) - scale(fCameraAngle, uScaleDepth)));
		float3 v3Attenuate = exp(-fScatter * (uInvWaveLength * uKr4PI + uKm4PI));
		v3Attenuate *= (fDepth * fScaledLength);
		color += v3Attenuate;
		v3SamplePoint += v3SampleRay;
	}

    oRayleighColor = color * (uInvWaveLength * uKrESun);
    oMieColor      = color * uKmESun;
    oDirection     = uCameraPos - v3Pos;
    oUV = iUV;
    oOpacity = iOpacity;
    oHeight = 1-iNPosition.y;
}

void main_fp(
    // IN
    float2 iUV              : TEXCOORD0,
	float3 iRayleighColor   : TEXCOORD1,
	float3 iMieColor        : TEXCOORD2,
	float3 iDirection       : TEXCOORD3,
	float  iOpacity         : TEXCOORD4,
	float  iHeight          : TEXCOORD5,
	
	// OUT 
	out float4 oColor		: COLOR,
	
	// UNIFORM
	uniform float  uTime,
	uniform float3 uLightDir,
	
    // Phase function
	uniform float  uG,
	uniform float  uG2,
	uniform float  uExposure,
	uniform sampler2D uStarfield : register(s0)
	)
{
    float cos = dot(uLightDir, iDirection) / length(iDirection);
	float cos2 = cos*cos;
	float rayleighPhase = 0.75 * (1.0 + 0.5*cos2);
	float miePhase = 1.5f * ((1.0f - uG2) / (2.0f + uG2)) * (1.0f + cos2) / pow(1.0f + uG2 - 2.0f * uG * cos, 1.5f);
    oColor = float4(uExposure * (rayleighPhase * iRayleighColor + miePhase * iMieColor), iOpacity);
	float nightmult = saturate(1 - max(oColor.x, max(oColor.y, oColor.z))*10);
	oColor.xyz += nightmult *(pow(float3(0.05, 0.05, 0.1)*(2-0.75*saturate(-uLightDir.y))*pow(iHeight,3),2.2) + tex2D(uStarfield, iUV+uTime)*(0.35f + saturate(-uLightDir.y*0.45f))); 
}