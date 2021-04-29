#ifndef GPUSTRUCTS_H
#define GPUSTRUCTS_H

// Float4 is typedefed as XMFLOAT4 in stdafx.h

struct ConstantBuffer
{
	float4x4 wvpMatrix;
	float4 colorMultiplier;
};




#endif