# in root pro file set the CONFIG
# CONFIG += C++11

INCLUDEPATH += $$PWD/

DEFINES += _CRT_SECURE_NO_WARNINGS


HEADERS += \
    $$PWD/glm/detail/_features.hpp \
    $$PWD/glm/detail/_fixes.hpp \
    $$PWD/glm/detail/_noise.hpp \
    $$PWD/glm/detail/_swizzle.hpp \
    $$PWD/glm/detail/_swizzle_func.hpp \
    $$PWD/glm/detail/_vectorize.hpp \
    $$PWD/glm/detail/func_common.hpp \
    $$PWD/glm/detail/func_exponential.hpp \
    $$PWD/glm/detail/func_geometric.hpp \
    $$PWD/glm/detail/func_integer.hpp \
    $$PWD/glm/detail/func_matrix.hpp \
    $$PWD/glm/detail/func_packing.hpp \
    $$PWD/glm/detail/func_trigonometric.hpp \
    $$PWD/glm/detail/func_vector_relational.hpp \
    $$PWD/glm/detail/intrinsic_common.hpp \
    $$PWD/glm/detail/intrinsic_exponential.hpp \
    $$PWD/glm/detail/intrinsic_geometric.hpp \
    $$PWD/glm/detail/intrinsic_integer.hpp \
    $$PWD/glm/detail/intrinsic_matrix.hpp \
    $$PWD/glm/detail/intrinsic_trigonometric.hpp \
    $$PWD/glm/detail/intrinsic_vector_relational.hpp \
    $$PWD/glm/detail/precision.hpp \
    $$PWD/glm/detail/setup.hpp \
    $$PWD/glm/detail/type_float.hpp \
    $$PWD/glm/detail/type_gentype.hpp \
    $$PWD/glm/detail/type_half.hpp \
    $$PWD/glm/detail/type_int.hpp \
    $$PWD/glm/detail/type_mat.hpp \
    $$PWD/glm/detail/type_mat2x2.hpp \
    $$PWD/glm/detail/type_mat2x3.hpp \
    $$PWD/glm/detail/type_mat2x4.hpp \
    $$PWD/glm/detail/type_mat3x2.hpp \
    $$PWD/glm/detail/type_mat3x3.hpp \
    $$PWD/glm/detail/type_mat3x4.hpp \
    $$PWD/glm/detail/type_mat4x2.hpp \
    $$PWD/glm/detail/type_mat4x3.hpp \
    $$PWD/glm/detail/type_mat4x4.hpp \
    $$PWD/glm/detail/type_vec.hpp \
    $$PWD/glm/detail/type_vec1.hpp \
    $$PWD/glm/detail/type_vec2.hpp \
    $$PWD/glm/detail/type_vec3.hpp \
    $$PWD/glm/detail/type_vec4.hpp \
    $$PWD/glm/gtc/bitfield.hpp \
    $$PWD/glm/gtc/color_space.hpp \
    $$PWD/glm/gtc/constants.hpp \
    $$PWD/glm/gtc/epsilon.hpp \
    $$PWD/glm/gtc/integer.hpp \
    $$PWD/glm/gtc/matrix_access.hpp \
    $$PWD/glm/gtc/matrix_integer.hpp \
    $$PWD/glm/gtc/matrix_inverse.hpp \
    $$PWD/glm/gtc/matrix_transform.hpp \
    $$PWD/glm/gtc/noise.hpp \
    $$PWD/glm/gtc/packing.hpp \
    $$PWD/glm/gtc/quaternion.hpp \
    $$PWD/glm/gtc/random.hpp \
    $$PWD/glm/gtc/reciprocal.hpp \
    $$PWD/glm/gtc/round.hpp \
    $$PWD/glm/gtc/type_precision.hpp \
    $$PWD/glm/gtc/type_ptr.hpp \
    $$PWD/glm/gtc/ulp.hpp \
    $$PWD/glm/gtc/vec1.hpp \
    $$PWD/glm/gtx/associated_min_max.hpp \
    $$PWD/glm/gtx/bit.hpp \
    $$PWD/glm/gtx/closest_point.hpp \
    $$PWD/glm/gtx/color_space.hpp \
    $$PWD/glm/gtx/color_space_YCoCg.hpp \
    $$PWD/glm/gtx/common.hpp \
    $$PWD/glm/gtx/compatibility.hpp \
    $$PWD/glm/gtx/component_wise.hpp \
    $$PWD/glm/gtx/dual_quaternion.hpp \
    $$PWD/glm/gtx/euler_angles.hpp \
    $$PWD/glm/gtx/extend.hpp \
    $$PWD/glm/gtx/extented_min_max.hpp \
    $$PWD/glm/gtx/fast_exponential.hpp \
    $$PWD/glm/gtx/fast_square_root.hpp \
    $$PWD/glm/gtx/fast_trigonometry.hpp \
    $$PWD/glm/gtx/gradient_paint.hpp \
    $$PWD/glm/gtx/handed_coordinate_space.hpp \
    $$PWD/glm/gtx/hash.hpp \
    $$PWD/glm/gtx/integer.hpp \
    $$PWD/glm/gtx/intersect.hpp \
    $$PWD/glm/gtx/io.hpp \
    $$PWD/glm/gtx/log_base.hpp \
    $$PWD/glm/gtx/matrix_cross_product.hpp \
    $$PWD/glm/gtx/matrix_decompose.hpp \
    $$PWD/glm/gtx/matrix_interpolation.hpp \
    $$PWD/glm/gtx/matrix_major_storage.hpp \
    $$PWD/glm/gtx/matrix_operation.hpp \
    $$PWD/glm/gtx/matrix_query.hpp \
    $$PWD/glm/gtx/matrix_transform_2d.hpp \
    $$PWD/glm/gtx/mixed_product.hpp \
    $$PWD/glm/gtx/norm.hpp \
    $$PWD/glm/gtx/normal.hpp \
    $$PWD/glm/gtx/normalize_dot.hpp \
    $$PWD/glm/gtx/number_precision.hpp \
    $$PWD/glm/gtx/optimum_pow.hpp \
    $$PWD/glm/gtx/orthonormalize.hpp \
    $$PWD/glm/gtx/perpendicular.hpp \
    $$PWD/glm/gtx/polar_coordinates.hpp \
    $$PWD/glm/gtx/projection.hpp \
    $$PWD/glm/gtx/quaternion.hpp \
    $$PWD/glm/gtx/range.hpp \
    $$PWD/glm/gtx/raw_data.hpp \
    $$PWD/glm/gtx/rotate_normalized_axis.hpp \
    $$PWD/glm/gtx/rotate_vector.hpp \
    $$PWD/glm/gtx/scalar_multiplication.hpp \
    $$PWD/glm/gtx/scalar_relational.hpp \
    $$PWD/glm/gtx/simd_mat4.hpp \
    $$PWD/glm/gtx/simd_quat.hpp \
    $$PWD/glm/gtx/simd_vec4.hpp \
    $$PWD/glm/gtx/spline.hpp \
    $$PWD/glm/gtx/std_based_type.hpp \
    $$PWD/glm/gtx/string_cast.hpp \
    $$PWD/glm/gtx/transform.hpp \
    $$PWD/glm/gtx/transform2.hpp \
    $$PWD/glm/gtx/type_aligned.hpp \
    $$PWD/glm/gtx/vector_angle.hpp \
    $$PWD/glm/gtx/vector_query.hpp \
    $$PWD/glm/gtx/wrap.hpp \
    $$PWD/glm/common.hpp \
    $$PWD/glm/exponential.hpp \
    $$PWD/glm/ext.hpp \
    $$PWD/glm/fwd.hpp \
    $$PWD/glm/geometric.hpp \
    $$PWD/glm/glm.hpp \
    $$PWD/glm/integer.hpp \
    $$PWD/glm/mat2x2.hpp \
    $$PWD/glm/mat2x3.hpp \
    $$PWD/glm/mat2x4.hpp \
    $$PWD/glm/mat3x2.hpp \
    $$PWD/glm/mat3x3.hpp \
    $$PWD/glm/mat3x4.hpp \
    $$PWD/glm/mat4x2.hpp \
    $$PWD/glm/mat4x3.hpp \
    $$PWD/glm/mat4x4.hpp \
    $$PWD/glm/matrix.hpp \
    $$PWD/glm/packing.hpp \
    $$PWD/glm/trigonometric.hpp \
    $$PWD/glm/vec2.hpp \
    $$PWD/glm/vec3.hpp \
    $$PWD/glm/vec4.hpp \
    $$PWD/glm/vector_relational.hpp

SOURCES += \
#    $$PWD/glm/detail/dummy.cpp \
#    $$PWD/glm/detail/func_common.inl \
#    $$PWD/glm/detail/func_exponential.inl \
#    $$PWD/glm/detail/func_geometric.inl \
#    $$PWD/glm/detail/func_integer.inl \
#    $$PWD/glm/detail/func_matrix.inl \
#    $$PWD/glm/detail/func_packing.inl \
#    $$PWD/glm/detail/func_trigonometric.inl \
#    $$PWD/glm/detail/func_vector_relational.inl \
    $$PWD/glm/detail/glm.cpp \
#    $$PWD/glm/detail/intrinsic_common.inl \
#    $$PWD/glm/detail/intrinsic_exponential.inl \
#    $$PWD/glm/detail/intrinsic_geometric.inl \
#    $$PWD/glm/detail/intrinsic_integer.inl \
#    $$PWD/glm/detail/intrinsic_matrix.inl \
#    $$PWD/glm/detail/intrinsic_trigonometric.inl \
#    $$PWD/glm/detail/intrinsic_vector_relational.inl \
#    $$PWD/glm/detail/type_gentype.inl \
#    $$PWD/glm/detail/type_half.inl \
#    $$PWD/glm/detail/type_mat.inl \
#    $$PWD/glm/detail/type_mat2x2.inl \
#    $$PWD/glm/detail/type_mat2x3.inl \
#    $$PWD/glm/detail/type_mat2x4.inl \
#    $$PWD/glm/detail/type_mat3x2.inl \
#    $$PWD/glm/detail/type_mat3x3.inl \
#    $$PWD/glm/detail/type_mat3x4.inl \
#    $$PWD/glm/detail/type_mat4x2.inl \
#    $$PWD/glm/detail/type_mat4x3.inl \
#    $$PWD/glm/detail/type_mat4x4.inl \
#    $$PWD/glm/detail/type_vec.inl \
#    $$PWD/glm/detail/type_vec1.inl \
#    $$PWD/glm/detail/type_vec2.inl \
#    $$PWD/glm/detail/type_vec3.inl \
#    $$PWD/glm/detail/type_vec4.inl \
#    $$PWD/glm/detail/type_vec4_avx.inl \
#    $$PWD/glm/detail/type_vec4_avx2.inl \
#    $$PWD/glm/detail/type_vec4_sse2.inl \
#    $$PWD/glm/gtc/bitfield.inl \
#    $$PWD/glm/gtc/color_space.inl \
#    $$PWD/glm/gtc/constants.inl \
#    $$PWD/glm/gtc/epsilon.inl \
#    $$PWD/glm/gtc/integer.inl \
#    $$PWD/glm/gtc/matrix_access.inl \
#    $$PWD/glm/gtc/matrix_inverse.inl \
#    $$PWD/glm/gtc/matrix_transform.inl \
#    $$PWD/glm/gtc/noise.inl \
#    $$PWD/glm/gtc/packing.inl \
#    $$PWD/glm/gtc/quaternion.inl \
#    $$PWD/glm/gtc/random.inl \
#    $$PWD/glm/gtc/reciprocal.inl \
#    $$PWD/glm/gtc/round.inl \
#    $$PWD/glm/gtc/type_precision.inl \
#    $$PWD/glm/gtc/type_ptr.inl \
#    $$PWD/glm/gtc/ulp.inl \
#    $$PWD/glm/gtc/vec1.inl \
#    $$PWD/glm/gtx/associated_min_max.inl \
#    $$PWD/glm/gtx/bit.inl \
#    $$PWD/glm/gtx/closest_point.inl \
#    $$PWD/glm/gtx/color_space.inl \
#    $$PWD/glm/gtx/color_space_YCoCg.inl \
#    $$PWD/glm/gtx/common.inl \
#    $$PWD/glm/gtx/compatibility.inl \
#    $$PWD/glm/gtx/component_wise.inl \
#    $$PWD/glm/gtx/dual_quaternion.inl \
#    $$PWD/glm/gtx/euler_angles.inl \
#    $$PWD/glm/gtx/extend.inl \
#    $$PWD/glm/gtx/extented_min_max.inl \
#    $$PWD/glm/gtx/fast_exponential.inl \
#    $$PWD/glm/gtx/fast_square_root.inl \
#    $$PWD/glm/gtx/fast_trigonometry.inl \
#    $$PWD/glm/gtx/gradient_paint.inl \
#    $$PWD/glm/gtx/handed_coordinate_space.inl \
#    $$PWD/glm/gtx/hash.inl \
#    $$PWD/glm/gtx/integer.inl \
#    $$PWD/glm/gtx/intersect.inl \
#    $$PWD/glm/gtx/io.inl \
#    $$PWD/glm/gtx/log_base.inl \
#    $$PWD/glm/gtx/matrix_cross_product.inl \
#    $$PWD/glm/gtx/matrix_decompose.inl \
#    $$PWD/glm/gtx/matrix_interpolation.inl \
#    $$PWD/glm/gtx/matrix_major_storage.inl \
#    $$PWD/glm/gtx/matrix_operation.inl \
#    $$PWD/glm/gtx/matrix_query.inl \
#    $$PWD/glm/gtx/matrix_transform_2d.inl \
#    $$PWD/glm/gtx/mixed_product.inl \
#    $$PWD/glm/gtx/norm.inl \
#    $$PWD/glm/gtx/normal.inl \
#    $$PWD/glm/gtx/normalize_dot.inl \
#    $$PWD/glm/gtx/number_precision.inl \
#    $$PWD/glm/gtx/optimum_pow.inl \
#    $$PWD/glm/gtx/orthonormalize.inl \
#    $$PWD/glm/gtx/perpendicular.inl \
#    $$PWD/glm/gtx/polar_coordinates.inl \
#    $$PWD/glm/gtx/projection.inl \
#    $$PWD/glm/gtx/quaternion.inl \
#    $$PWD/glm/gtx/raw_data.inl \
#    $$PWD/glm/gtx/rotate_normalized_axis.inl \
#    $$PWD/glm/gtx/rotate_vector.inl \
#    $$PWD/glm/gtx/scalar_relational.inl \
#    $$PWD/glm/gtx/simd_mat4.inl \
#    $$PWD/glm/gtx/simd_quat.inl \
#    $$PWD/glm/gtx/simd_vec4.inl \
#    $$PWD/glm/gtx/spline.inl \
#    $$PWD/glm/gtx/std_based_type.inl \
#    $$PWD/glm/gtx/string_cast.inl \
#    $$PWD/glm/gtx/transform.inl \
#    $$PWD/glm/gtx/transform2.inl \
#    $$PWD/glm/gtx/type_aligned.inl \
#    $$PWD/glm/gtx/vector_angle.inl \
#    $$PWD/glm/gtx/vector_query.inl \
#    $$PWD/glm/gtx/wrap.inl

DISTFILES += \
    $$PWD/glm/CMakeLists.txt
