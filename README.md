`
### CPU Cache Simulator (C++)
### 📌 Problem Statement
```
Modern processors rely heavily on cache memory to bridge the speed gap between the CPU and main memory.
Understanding cache behavior is crucial for analyzing system performance.
This project implements a CPU Cache Simulator that models cache operations and evaluates performance
in terms of cache hits and misses for a given memory access trace.
```

### ⚙️ Features
```
Set-Associative Cache Mapping
LRU (Least Recently Used) Replacement Policy
Configurable cache parameters
Address decoding into Tag, Index, and Offset
Cache hit and miss detection
Cache performance analysis
```
### 🧠 Cache Design
```
Cache is divided into sets, each containing multiple cache lines
Each cache line stores:
Valid bit
Tag
LRU counter
Memory addresses are decoded into:
Tag
Set Index
Block Offset

On a cache miss:
An empty line is used if available
Otherwise, the LRU line is replaced
```
### 📥 Input
```
trace.txt : Contains a sequence of memory addresses
Each address is processed sequentially to simulate cache behavior
```
### 📤 Output
```
Total number of memory accesses
Number of cache hits
Number of cache misses
Hit ratio and miss ratio (if implemented)
```
### ▶️ How to Run
```
Using Executable (Windows)
cache_sim.exe

Compile from Source
g++ cache_simulator.cpp -o cache_sim
./cache_sim

Make sure trace.txt is present in the same directory.
```

### 🧪 Example Use Case
```
Analyze how different cache configurations affect performance
Study the impact of associativity and replacement policies
Useful for Computer Architecture coursework and experiments
```
### 🛠 Technologies Used
```
Language: C++

Concepts:
Computer Architecture
Cache Memory
Set-Associative Mapping
LRU Replacement Policy
```
### 🎯 Learning Outcomes
```
Practical understanding of CPU cache operations
Experience with low-level system simulation
Improved knowledge of performance analysis techniques
```
### 📌 Future Enhancements
```
Support for write policies (Write-Through / Write-Back)
Multi-level cache simulation
Graphical visualization of cache performance
Command-line configuration of cache parameters
```
