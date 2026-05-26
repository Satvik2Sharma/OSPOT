# OSPOT (OS Performance Observation Tool)

**OSPOT** is a lightweight, low-level system performance monitoring utility designed for Linux environments. It interfaces directly with the Linux virtual filesystem to extract high-fidelity telemetry regarding hardware utilization and system state.

## 🧬 System Architecture

OSPOT bypasses high-level system APIs to read raw hardware telemetry directly from the kernel's virtual file system.

```text
    [ OSPOT Core Engine ]
              |
      +-------+-------+
      |               |
 [ /proc/stat ]  [ /proc/meminfo ]
  (CPU/System)     (Mem/Alloc)
      |               |
      +-------+-------+
              |
    [ Telemetry Aggregator ]
              |
      [ ospot_report.txt ]
```

## 🚀 Quick Start

### Compilation
OSPOT is written in raw C++ and requires `g++` (GCC) to compile. Run the following command in the project directory:

```bash
g++ ospot.cpp -o ospot
```

### Execution
Once compiled, execute the binary to generate a system performance snapshot:

```bash
./ospot
```
*Note: This will generate an `ospot_report.txt` file containing the latest telemetry data.*
