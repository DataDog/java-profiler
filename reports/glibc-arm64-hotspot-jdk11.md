---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 02:36:37 EDT

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
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790663473 48
1790663478 48
1790663483 48
1790663488 48
1790663493 48
1790663498 48
1790663503 48
1790663508 48
1790663513 48
1790663518 48
1790663523 48
1790663528 48
1790663533 48
1790663538 48
1790663543 48
1790663548 48
1790663553 48
1790663558 48
1790663563 48
1790663568 46
```
</details>

---

