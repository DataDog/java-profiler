---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 16:31:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 14 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1790281590 50
1790281595 50
1790281600 50
1790281605 50
1790281610 50
1790281615 50
1790281620 50
1790281625 50
1790281630 50
1790281635 50
1790281640 45
1790281645 45
1790281650 45
1790281655 45
1790281660 45
1790281665 45
1790281670 45
1790281675 45
1790281680 45
1790281685 45
```
</details>

---

