---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 01:13:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
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
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 926 |
| Sample Rate | 15.43/sec |
| Health Score | 964% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1792645590 48
1792645595 48
1792645600 48
1792645605 48
1792645610 48
1792645615 48
1792645620 48
1792645625 48
1792645630 48
1792645635 48
1792645640 48
1792645645 48
1792645650 48
1792645655 48
1792645660 48
1792645665 46
1792645670 46
1792645675 46
1792645680 46
1792645685 46
```
</details>

---

