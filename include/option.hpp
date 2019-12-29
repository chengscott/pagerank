#pragma once

namespace BuildOption {
enum class MatrixGemmType { Naive, NaiveTiling, MKL };

#ifdef USE_MKL
const constexpr auto MatrixGemm = MatrixGemmType::MKL;
#elif USE_TILING
const constexpr auto MatrixGemm = MatrixGemmType::NaiveTiling;
#else
const constexpr auto MatrixGemm = MatrixGemmType::Naive;
#endif
} // namespace BuildOption