// Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "lite/kernels/x86/calib_compute.h"

#include <vector>
#include "lite/backends/x86/math/calib.h"
#include "lite/core/op_registry.h"
#include "lite/core/type_system.h"

namespace paddle {
namespace lite {
namespace kernels {
namespace x86 {

template <DataLayoutType DLType>
void CalibComputeFp32ToInt8<DLType>::Run() {
  auto& param = this->template Param<operators::CalibParam>();
  std::vector<float> scale = {param.scale};
  const auto* din = param.input->template data<float>();
  auto* dout = param.output->template mutable_data<signed char>();
  lite::x86::math::fp32_to_int8(
      din, dout, scale.data(), 1, 1, param.input->numel());
}

template <DataLayoutType DLType>
void CalibComputeInt64ToInt32<DLType>::Run() {
  auto& param = this->template Param<operators::CalibParam>();
  const auto* din = param.input->template data<int64_t>();
  auto* dout = param.output->template mutable_data<int32_t>();
  for (auto i = 0; i < param.input->numel(); ++i) {
    dout[i] = static_cast<int32_t>(din[i]);
  }
}

template <DataLayoutType DLType>
void CalibComputeInt32ToInt64<DLType>::Run() {
  auto& param = this->template Param<operators::CalibParam>();
  const auto* din = param.input->template data<int32_t>();
  auto* dout = param.output->template mutable_data<int64_t>();
  for (auto i = 0; i < param.input->numel(); ++i) {
    dout[i] = static_cast<int64_t>(din[i]);
  }
}

template <DataLayoutType DLType>
void CalibComputeInt8ToFp32<DLType>::Run() {
  auto& param = this->template Param<operators::CalibParam>();
  const auto* din = param.input->template data<signed char>();
  std::vector<float> scale = {param.scale};
  auto* dout = param.output->template mutable_data<float>();
  lite::x86::math::int8_to_fp32(
      din, dout, scale.data(), 1, 1, param.input->numel());
}

template <DataLayoutType DLType>
void CalibComputeInt32ToFp32<DLType>::Run() {
  auto& param = this->template Param<operators::CalibParam>();
  const auto* din = param.input->template data<int32_t>();
  auto* dout = param.output->template mutable_data<float>();
  for (auto i = 0; i < param.input->numel(); ++i) {
    dout[i] = static_cast<float>(din[i]);
  }
}

template <DataLayoutType DLType>
void CalibComputeFp32ToInt32<DLType>::Run() {
  auto& param = this->template Param<operators::CalibParam>();
  const auto* din = param.input->template data<float>();
  auto* dout = param.output->template mutable_data<int32_t>();
  for (auto i = 0; i < param.input->numel(); ++i) {
    dout[i] = static_cast<int32_t>(din[i]);
  }
}

template <DataLayoutType DLType>
void CalibComputeInt64ToFp32<DLType>::Run() {
  auto& param = this->template Param<operators::CalibParam>();
  const auto* din = param.input->template data<int64_t>();
  auto* dout = param.output->template mutable_data<float>();
  for (auto i = 0; i < param.input->numel(); ++i) {
    dout[i] = static_cast<float>(din[i]);
  }
}

}  // namespace x86
}  // namespace kernels
}  // namespace lite
}  // namespace paddle

REGISTER_LITE_KERNEL(
    calib,
    kX86,
    kInt8,
    kNCHW,
    paddle::lite::kernels::x86::CalibComputeFp32ToInt8<DATALAYOUT(kNCHW)>,
    fp32_to_int8)
    .BindInput("Input",
               {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kFloat))})
    .BindOutput("Out", {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kInt8))})
    .Finalize();

REGISTER_LITE_KERNEL(
    calib,
    kX86,
    kInt32,
    kNCHW,
    paddle::lite::kernels::x86::CalibComputeInt32ToFp32<DATALAYOUT(kNCHW)>,
    int32_to_fp32)
    .BindInput("Input",
               {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kInt32))})
    .BindOutput("Out", {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kFloat))})
    .Finalize();

REGISTER_LITE_KERNEL(
    calib,
    kX86,
    kInt32,
    kNCHW,
    paddle::lite::kernels::x86::CalibComputeInt32ToInt64<DATALAYOUT(kNCHW)>,
    int32_to_int64)
    .BindInput("Input",
               {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kInt32))})
    .BindOutput("Out", {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kInt64))})
    .Finalize();

REGISTER_LITE_KERNEL(
    calib,
    kX86,
    kInt32,
    kNCHW,
    paddle::lite::kernels::x86::CalibComputeFp32ToInt32<DATALAYOUT(kNCHW)>,
    fp32_to_int32)
    .BindInput("Input",
               {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kFloat))})
    .BindOutput("Out", {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kInt32))})
    .Finalize();

REGISTER_LITE_KERNEL(
    calib,
    kX86,
    kInt64,
    kNCHW,
    paddle::lite::kernels::x86::CalibComputeInt64ToFp32<DATALAYOUT(kNCHW)>,
    int64_to_fp32)
    .BindInput("Input",
               {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kInt64))})
    .BindOutput("Out", {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kFloat))})
    .Finalize();

REGISTER_LITE_KERNEL(
    calib,
    kX86,
    kInt8,
    kNCHW,
    paddle::lite::kernels::x86::CalibComputeInt8ToFp32<DATALAYOUT(kNCHW)>,
    int8_to_fp32)
    .BindInput("Input", {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kInt8))})
    .BindOutput("Out", {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kFloat))})
    .Finalize();

REGISTER_LITE_KERNEL(
    calib,
    kX86,
    kInt64,
    kNCHW,
    paddle::lite::kernels::x86::CalibComputeInt64ToInt32<DATALAYOUT(kNCHW)>,
    int64_to_int32)
    .BindInput("Input",
               {LiteType::GetTensorTy(TARGET(kX86),
                                      PRECISION(kInt64),
                                      DATALAYOUT(kNCHW))})
    .BindOutput("Out",
                {LiteType::GetTensorTy(TARGET(kX86),
                                       PRECISION(kInt32),
                                       DATALAYOUT(kNCHW))})
    .Finalize();

REGISTER_LITE_KERNEL(
    calib_once,
    kX86,
    kInt8,
    kNCHW,
    paddle::lite::kernels::x86::CalibComputeFp32ToInt8<DATALAYOUT(kNCHW)>,
    fp32_to_int8)
    .BindInput("Input",
               {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kFloat))})
    .BindOutput("Out", {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kInt8))})
    .Finalize();

REGISTER_LITE_KERNEL(
    calib_once,
    kX86,
    kInt8,
    kNCHW,
    paddle::lite::kernels::x86::CalibComputeInt8ToFp32<DATALAYOUT(kNCHW)>,
    int8_to_fp32)
    .BindInput("Input", {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kInt8))})
    .BindOutput("Out", {LiteType::GetTensorTy(TARGET(kX86), PRECISION(kFloat))})
    .Finalize();

REGISTER_LITE_KERNEL(
    calib_once,
    kX86,
    kInt64,
    kNCHW,
    paddle::lite::kernels::x86::CalibComputeInt64ToInt32<DATALAYOUT(kNCHW)>,
    int64_to_int32)
    .BindInput("Input",
               {LiteType::GetTensorTy(TARGET(kX86),
                                      PRECISION(kInt64),
                                      DATALAYOUT(kNCHW))})
    .BindOutput("Out",
                {LiteType::GetTensorTy(TARGET(kX86),
                                       PRECISION(kInt32),
                                       DATALAYOUT(kNCHW))})
    .Finalize();
