/* Copyright (c) 2021 paddlepaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once

#ifdef __AVX2__

#include <stdint.h>

namespace paddle {
namespace lite {
namespace x86 {
namespace math {

void gemm_kernel_loop_int8(int M,
                           int N,
                           int K,
                           int8_t* A,
                           uint8_t* B,
                           int8_t* C,
                           int ldc,
                           const float* scale,
                           const float* bias,
                           int relu_type,
                           float relu_alpha);

void gemm_kernel_loop_int8(int M,
                           int N,
                           int K,
                           int8_t* A,
                           uint8_t* B,
                           float* C,
                           int ldc,
                           const float* scale,
                           const float* bias,
                           int relu_type,
                           float relu_alpha);

}  // namespace math
}  // namespace x86
}  // namespace lite
}  // namespace paddle

#endif  // __AVX2__
