---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 15:45:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1793130039 64
1793130044 64
1793130049 64
1793130054 64
1793130059 64
1793130064 64
1793130069 64
1793130074 64
1793130079 64
1793130084 64
1793130089 64
1793130094 64
1793130099 64
1793130104 64
1793130109 64
1793130114 64
1793130119 64
1793130124 64
1793130129 64
1793130134 64
```
</details>

---

