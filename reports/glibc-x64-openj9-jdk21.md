---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-30 10:30:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (6 unique values: 69-81 cores)</summary>

```
1777559055 79
1777559060 79
1777559065 79
1777559070 74
1777559075 74
1777559080 69
1777559085 69
1777559090 69
1777559095 69
1777559100 69
1777559105 69
1777559110 69
1777559115 72
1777559120 72
1777559125 72
1777559130 75
1777559135 75
1777559140 75
1777559145 75
1777559150 75
```
</details>

---

