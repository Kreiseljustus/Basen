#pragma once

#include <bx/math.h>

#include "Math/Types.h"

struct TransformComponent {
	float position[3] = { 0.0f, 0.0f, 0.0f };
	float rotation[3] = { 0.0f,0.0f,0.0f };
	float scale[3] = { 1.0f, 1.0f, 1.0f };

	Mat4 GetTransform() const {
		Mat4 transform;

		float mtxScale[16];
		float mtxRotation[16];
		float mtxTransform[16];

		float mtxScaleRotation[16];

		//Scale -> Rotation -> Position

		bx::mtxScale(mtxScale, scale[0], scale[1], scale[2]);
		bx::mtxRotateXYZ(mtxRotation, rotation[0], rotation[1], rotation[2]);
		bx::mtxTranslate(mtxTransform, position[0], position[1], position[2]);

		bx::mtxMul(mtxScaleRotation, mtxScale, mtxRotation);
		bx::mtxMul(transform.data, mtxScaleRotation, mtxTransform);

		return transform;
	}
};