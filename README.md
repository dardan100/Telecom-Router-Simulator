# Telecom Network Node Simulator (C++)

A highly optimized packet routing simulator built in modern **C++17**, demonstrating advanced object-oriented design and memory safety.

## ⚡ Engineering Architecture & Core Features

* **Polymorphism & Abstract Classes**: Architecture built upon a `Packet` base class with derived `VoicePacket` and `DataPacket` entities to handle specific payload rules dynamically.
* **Smart Pointers (`std::unique_ptr`)**: Implemented strict modern RAII principles. Zero raw pointers (`new`/`delete`) are used, fully eliminating the risk of memory leaks.
* **Priority Queue for QoS (Quality of Service)**: Instead of linear queues (`O(n)`), the routing buffer utilizes a `std::priority_queue` (`O(log n)` insertion). This ensures time-sensitive VoIP packets dynamically bypass standard data packets, mimicking real-world Ericsson network nodes.
* **Zero-Copy Overhead**: Packet ownership is strictly transferred via `std::move()` semantics, preventing expensive deep-copy operations during routing.
