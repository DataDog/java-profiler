---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 09:06:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 37-46 cores)</summary>

```
1790168523 46
1790168528 46
1790168533 46
1790168538 46
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

