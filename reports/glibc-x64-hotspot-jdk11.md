---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-26 16:34:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1777235458 32
1777235463 32
1777235468 32
1777235473 32
1777235478 32
1777235483 32
1777235488 32
1777235493 30
1777235498 30
1777235503 30
1777235508 30
1777235513 30
1777235518 30
1777235523 32
1777235528 32
1777235533 32
1777235538 32
1777235543 32
1777235548 32
1777235553 32
```
</details>

---

