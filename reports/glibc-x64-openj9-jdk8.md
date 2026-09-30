---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-30 07:31:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 334 |
| Sample Rate | 5.57/sec |
| Health Score | 348% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 34-40 cores)</summary>

```
1790767625 36
1790767630 34
1790767635 34
1790767640 34
1790767645 36
1790767650 36
1790767655 38
1790767660 38
1790767665 38
1790767670 38
1790767675 38
1790767680 38
1790767685 38
1790767690 38
1790767695 40
1790767700 40
1790767705 40
1790767710 40
1790767715 40
1790767720 40
```
</details>

---

