---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 09:27:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 14 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1786454479 32
1786454484 32
1786454489 32
1786454494 32
1786454499 32
1786454504 32
1786454509 32
1786454514 32
1786454519 32
1786454524 32
1786454529 32
1786454534 32
1786454539 32
1786454544 27
1786454549 27
1786454554 27
1786454559 27
1786454564 27
1786454569 27
1786454574 27
```
</details>

---

