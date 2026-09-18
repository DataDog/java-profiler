---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:23:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 9 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (7 unique values: 34-48 cores)</summary>

```
1789737459 48
1789737464 48
1789737469 48
1789737474 39
1789737479 39
1789737484 39
1789737489 39
1789737494 39
1789737499 39
1789737504 36
1789737509 36
1789737514 34
1789737519 34
1789737524 34
1789737529 34
1789737534 34
1789737539 34
1789737544 34
1789737549 34
1789737554 34
```
</details>

---

