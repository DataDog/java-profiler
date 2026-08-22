---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-22 05:27:12 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 8 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (4 unique values: 24-44 cores)</summary>

```
1787390479 29
1787390484 29
1787390489 34
1787390494 34
1787390499 34
1787390504 34
1787390509 34
1787390514 34
1787390519 24
1787390524 24
1787390529 29
1787390534 29
1787390539 44
1787390544 44
1787390549 44
1787390554 44
1787390559 44
1787390564 44
1787390569 44
1787390574 44
```
</details>

---

