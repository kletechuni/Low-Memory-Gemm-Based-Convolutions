# Low-Memory-Gemm-Based-Convolutions
Memory footprint reduction for GEMM computation for memory restricted devices.

Current Status:
- Installed ARM-NN SDK and currently facing issues with running unit tests.

- Building Arm Compute Library without SDK on ARM Cortex A53 board(Raspberry Pi 3 B), both natively and by cross compilation. Facing errors during builds of both.  Successful builds result in missing files.

- Implementing various low memory convolution algorithms in python and analysing memory usage difference from TensorFlow functions.  Currently searching for an appropriate memory profiler. We are using Heapy from Guppy package, but having trouble analysing results.

