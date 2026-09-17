---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 15:35:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 8 |
| Allocations | 319 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 10 |
| Allocations | 91 |

<details>
<summary>CPU Timeline (2 unique values: 10-30 cores)</summary>

```
1789673386 10
1789673391 10
1789673396 10
1789673401 10
1789673406 10
1789673411 10
1789673416 10
1789673421 30
1789673426 30
1789673431 30
1789673436 30
1789673441 30
1789673446 30
1789673451 30
1789673456 30
1789673461 30
1789673466 30
1789673471 30
1789673476 30
1789673481 30
```
</details>

---

