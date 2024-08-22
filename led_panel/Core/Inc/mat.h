/*
 * mat.h
 *
 *  Created on: Aug 21, 2024
 *      Author: han
 */

#ifndef INC_MAT_H_
#define INC_MAT_H_

typedef struct {
    float x, y, z, w;
} Vec4;


typedef struct {
	float m[4][4];
} Mat4;

typedef struct {
    float x, y, z;
    float rot_x, rot_y, rot_z;
    float scale_x, scale_y, scale_z;
} Transform;


//	Mat4 identity_matrix = {{
//			{1,0,0,0},
//			{0,1,0,0},
//			{0,0,1,0},
//			{0,0,0,1}
//	}};


Mat4 mat4_mul_mat4(const Mat4 *a, const Mat4 *b);
Vec4 mat4_mul_vec4(const Mat4 *m, const Vec4 *v);

Mat4 calculate_transform_matrix(const Transform *transform);

Mat4 mat4_make_perspective(float fov, float aspect, float znear, float zfar);
Vec4 mat4_mul_vec4_project(Mat4* mat_proj, Vec4* v);

Mat4 get_view_matrix(float cam_x, float cam_y, float cam_z);


#endif /* INC_MAT_H_ */
