---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 09:02:23 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 224 |
| Sample Rate | 3.73/sec |
| Health Score | 233% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 14 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789995428 48
1789995433 48
1789995438 48
1789995443 48
1789995448 48
1789995453 43
1789995458 43
1789995463 43
1789995468 43
1789995473 43
1789995478 43
1789995483 43
1789995488 43
1789995493 43
1789995498 43
1789995503 43
1789995508 43
1789995513 48
1789995518 48
1789995523 48
```
</details>

---

