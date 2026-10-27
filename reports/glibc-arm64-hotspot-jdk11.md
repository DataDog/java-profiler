---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 15:45:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 12 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (2 unique values: 12-13 cores)</summary>

```
1793130034 13
1793130039 13
1793130044 13
1793130049 13
1793130054 13
1793130059 13
1793130064 13
1793130069 13
1793130074 13
1793130079 13
1793130084 13
1793130089 13
1793130094 13
1793130099 13
1793130104 13
1793130109 13
1793130114 13
1793130119 13
1793130124 13
1793130129 13
```
</details>

---

