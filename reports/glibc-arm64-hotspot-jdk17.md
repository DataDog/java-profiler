---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 09:06:32 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 37-46 cores)</summary>

```
1790168523 46
1790168528 46
1790168533 46
1790168538 42
1790168543 42
1790168548 42
1790168553 37
1790168558 37
1790168563 39
1790168568 39
1790168573 39
1790168578 39
1790168583 39
1790168588 39
1790168593 39
1790168598 39
1790168603 39
1790168608 39
1790168613 39
1790168618 39
```
</details>

---

