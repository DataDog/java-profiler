---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-17 15:36:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 252 |
| Sample Rate | 4.20/sec |
| Health Score | 262% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1789673433 48
1789673438 48
1789673443 48
1789673448 48
1789673453 48
1789673458 48
1789673463 48
1789673468 48
1789673473 48
1789673478 48
1789673483 48
1789673488 48
1789673493 48
1789673498 48
1789673503 48
1789673508 48
1789673513 47
1789673518 47
1789673523 47
1789673528 47
```
</details>

---

