void main_vp(
    // IN
	float4 iPosition	        : POSITION,
	float2 iUV                  : TEXCOORD0,
	
	// OUT
	out float4 oPosition		: POSITION,
	out float4 oUVYLength       : TEXCOORD0,
	
	// UNIFORM
	uniform float4x4 uWorldViewProj,
	uniform float4x4 uWorld,
	uniform float3   uSkydomeCenter)
{
	oPosition   = mul(uWorldViewProj, iPosition);
	float3 ObjectSpacePosition = mul(uWorld, iPosition) - uSkydomeCenter;
    oUVYLength.xy = iUV;
    oUVYLength.z  = ObjectSpacePosition.y;
    oUVYLength.w  = length(ObjectSpacePosition);
}

void main_fp(
    // IN
    float4 iUVYLength       : TEXCOORD0,
	
	// OUT 
	out float4 oColor		: COLOR,
	
	// UNIFORM
	uniform float3    uMoonPhase,
	uniform float3    uMoonHalo1,
	uniform float3    uMoonHalo2,
	uniform float     uMoonHaloFlip,
	uniform sampler2D uMoon : register(s0),
	uniform sampler2D uMoonHalo : register(s1))
{
    oColor = tex2D(uMoon, iUVYLength.xy);
	float radius = abs(uMoonPhase.x);
	float2 center = float2(uMoonPhase.y, 0.5);
	float dist = length(iUVYLength.xy - center);
	float att = saturate((radius-dist+0.015)*40);
	if (uMoonHaloFlip > 0.5) { iUVYLength.x = 1-iUVYLength.x; }
	float2 haloUV = float2(iUVYLength.x/4, iUVYLength.y/2);
	float2 halo1UV = float2(uMoonHalo1.x + haloUV.x, uMoonHalo1.y + haloUV.y);
	float2 halo2UV = float2(uMoonHalo2.x + haloUV.x, uMoonHalo2.y + haloUV.y);
	float haloIntensity = tex2D(uMoonHalo, halo1UV).w*uMoonHalo1.z + tex2D(uMoonHalo, halo2UV).w*uMoonHalo2.z;
	haloIntensity = pow(haloIntensity, uMoonPhase.z);
	if (uMoonPhase.x > 0) {
		oColor.rgb *= 0.16 + (1-0.16)*(1-att);
		oColor.rgb += saturate(haloIntensity-oColor.r)*(1-(1-att)*oColor.a);
	} else {
		oColor.rgb *= 0.16 + (1-0.16)*att;
		oColor.rgb += saturate(haloIntensity-oColor.r)*(1-att*oColor.a);
	}	

	oColor.rgb += (1-oColor.a)*1.4*(1-pow(oColor.a,2*haloIntensity));
	oColor.rgb = saturate(oColor.rgb);
	oColor.a = max(oColor.a, haloIntensity);
	oColor.w *= saturate((iUVYLength.z/iUVYLength.w)*10);
}