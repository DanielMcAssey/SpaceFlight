float scale(float cos, float uScaleDepth)
{
	float x = 1.0 - cos;
	return uScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

void main_vp(
    // IN
	float4 iPosition	        : POSITION,
	
	// OUT
	out float4 oPosition		: POSITION,
	out float3 oRayleighColor   : TEXCOORD0,
	out float3 oDirection       : TEXCOORD1,
	
	// UNIFORM
	uniform float4x4 uWorldViewProj,
    uniform float4x4 uWorld,
	
	// Global information
	uniform float3 uLightDir,
	
	// Position information
	uniform float3 uCameraPos,
	uniform float3 uCameraPos_,
	uniform float3 uInvWaveLength,
	uniform float  uInnerRadius,
	
	// Scattering parameters
	uniform float  uKrESun, // Kr * ESun
	uniform float  uKr4PI,  // Kr * 4 * PI
	uniform float  uKm4PI,  // Km * 4 * PI
	
	// Atmosphere properties
	uniform float uScale,
	uniform float uScaleDepth,
	uniform float uScaleOverScaleDepth,
	uniform float uSkydomeRadius,
	
	// Number of samples
	uniform int   uNumberOfSamples,
	uniform float uSamples)
{
	oPosition = mul(uWorldViewProj, iPosition);
	float3 vertexWorldPos = mul(uWorld, iPosition);
	float3 v3Pos;
	v3Pos.xz = (vertexWorldPos.xz-uCameraPos_.xz) / uSkydomeRadius;
	v3Pos.y = uCameraPos.y + vertexWorldPos.y / uSkydomeRadius;
	float3 v3Ray = v3Pos - uCameraPos;
	float fFar = length(v3Ray);
	v3Ray /= fFar;
	
	float3 v3Start = uCameraPos; // Creo k ai k ajustar la posicion y del pixel
	float fDepth = exp((uInnerRadius - uCameraPos.y) / uScaleDepth);
	float fCameraAngle = dot(v3Ray, uCameraPos) / length(v3Pos);
	float fLightAngle = dot(normalize(uLightDir), v3Pos) / length(v3Pos);
	float fCameraScale = scale(fCameraAngle, uScaleDepth);
	float fLightScale = scale(fLightAngle, uScaleDepth);
	float fCameraOffset = fDepth*fCameraScale;
	float fTemp = (fLightScale + fCameraScale);
	float fSampleLength = fFar / uSamples;
	float fScaledLength = fSampleLength * uScale;
	float3 v3SampleRay = v3Ray * fSampleLength;
	float3 v3SamplePoint = v3Start + v3SampleRay * 0.5f;
	float3 color = float3(0,0,0);
	
	for (int i = 0; i < uNumberOfSamples; i++)
	{
    	float fHeight = length(v3SamplePoint);
		float fDepth = exp(uScaleOverScaleDepth * (uInnerRadius-fHeight));
		float fScatter = fDepth*fTemp - fCameraOffset;
		float3 v3Attenuate = exp(-fScatter * (uInvWaveLength * uKr4PI + uKm4PI));
		color += v3Attenuate * (fDepth * fScaledLength);
		v3SamplePoint += v3SampleRay;
	}

    oRayleighColor = color * (uInvWaveLength * uKrESun);
	oDirection     = uCameraPos - v3Pos;
}

void main_fp(
    // IN
	float3 iRayleighColor   : TEXCOORD0,
	float3 iDirection       : TEXCOORD1,
	
	// OUT 
	out float4 oColor		: COLOR,
	
	// UNIFORM
	uniform float3 uLightDir
	)
{	
	float cos = dot(uLightDir, iDirection) / length(iDirection);
	float cos2 = cos*cos;
	float rayleighPhase = 0.75 * (1.0 + 0.5*cos2);			 
	oColor = float4(rayleighPhase*iRayleighColor,1);
}