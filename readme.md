# CertAlloc: Formally Verified Memory Suite

CertAlloc is a high-performance, $O(1)$ constant-time pool memory allocator designed for safety-critical embedded systems. Unlike standard `malloc`, CertAlloc is architected to be deterministic, thread-safe, and formally verified against memory corruption.

## 🚀 Key Features

* **Formal Proofs:** Architecturally verified via TLA+; C-code logic verified via CBMC.
* **$O(1)$ Performance:** Constant-time allocation and deallocation using hardware-accelerated bitwise intrinsics.
* **Safety-Ready:** Built-in hardware critical section hooks for bare-metal (AVR/ARM) and POSIX (Linux/WSL) environments.
* **Audit-Ready:** Includes a full suite of verification artifacts, including formal proof logs and stress-test benchmarks.

---

## 🛠️ Repository Structure

* `include/`: Public API header (`certalloc.h`).
* `lib/`: Compiled static library (`libcertalloc.a`).
* `tools/`: Compiled static analyzer binary (`certalloc-analyzer`).
* `compliance/`: Formal proof logs (TLA+ and CBMC) and benchmark reports.

---

## 📋 Integration Instructions

### 1. Linking the Library

To use CertAlloc in your project, link the static library and include the public header:

```bash
# Example compilation command
gcc main.c -L./lib -lcertalloc -I./include -o product_app -pthread

```

### 2. Implementation

Initialize the allocator before performing any memory operations:

```c
#include "certalloc.h"

int main() {
    if (certalloc_init()) {
        void* ptr = cert_alloc(16);
        // ... perform operations ...
        cert_free(ptr);
    }
    return 0;
}

```

---

## 🧪 Verification & Testing

### Integration Validation

To verify the library is correctly linked and functional in your environment:

1. Create a `test_harness.c` calling `certalloc_init()`, `cert_alloc()`, and `cert_free()`.
2. Compile using the instructions above.
3. If the binary executes without segmentation faults, the library is correctly integrated.

### Static Memory Bounding

Use the provided `certalloc-analyzer` tool to scan your source tree and calculate the maximum theoretical memory requirements for your application:

```bash
./tools/certalloc-analyzer

```

---

## 🔒 Verification Evidence

This library comes with a pre-computed "Verification"

Drop me a whatsApp via +94 76 388 5727 or mail me at vindana@cyburndigital.com for proof. Only if you are interested.

* **TLA+ Proofs:** Proving architectural impossibility of deadlocks or double-allocations.
* <img width="971" height="455" alt="image" src="https://github.com/user-attachments/assets/4c1f1273-1d66-405b-a185-fb7e659cbbe2" />

* **CBMC Proofs:** Mathematical guarantee of zero buffer overflows or pointer alignment risks.
* <img width="969" height="413" alt="image" src="https://github.com/user-attachments/assets/61b83cfa-1cda-4d32-a5f7-23af55f8c622" />

* **Stress Test Logs:** Validated performance under 1,000,000 randomized operations with 0% memory leakage.

---

## ⚖️ License & Compliance

This software is provided as a **Qualification-Ready Component**. Please refer to the `compliance/` documentation when submitting this component for internal audits or external safety certifications (ISO 26262/IEC 62304).

---
