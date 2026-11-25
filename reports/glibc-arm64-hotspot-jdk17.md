---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 06:23:07 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795605473 33
1795605478 33
1795605483 33
1795605488 33
1795605493 33
1795605498 33
1795605503 33
1795605508 33
1795605513 33
1795605518 33
1795605523 33
1795605528 33
1795605533 33
1795605538 33
1795605543 33
1795605548 33
1795605553 33
1795605558 33
1795605563 33
1795605568 33
```
</details>

---

