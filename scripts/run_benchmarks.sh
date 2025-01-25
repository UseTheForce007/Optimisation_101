#!/bin/bash

# Run benchmarks with:
# - Color output
# - Detailed time measurements
# - CSV output for analysis
# - Filter for specific benchmarks if provided

BENCHMARK_BINARY="build/benchmarks/benchmarks"
OUTPUT_DIR="benchmark_results"
TIMESTAMP=$(date +%Y%m%d_%H%M%S)
OUTPUT_FILE="${OUTPUT_DIR}/benchmark_${TIMESTAMP}.csv"

# Create output directory if it doesn't exist
mkdir -p ${OUTPUT_DIR}

# Run benchmarks with specified options
${BENCHMARK_BINARY} \
    --benchmark_format=csv \
    --benchmark_out=${OUTPUT_FILE} \
    --benchmark_color=true \
    --benchmark_time_unit=ms \
    "$@"

if [ $? -eq 0 ]; then
    echo -e "\033[32mBenchmarks ran successfully.\033[0m"
    echo "Results saved to: ${OUTPUT_FILE}"
else
    echo -e "\033[31mBenchmarks failed to run.\033[0m"
    exit 1
fi