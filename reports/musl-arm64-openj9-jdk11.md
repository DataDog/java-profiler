---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 10:43:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 9 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1790692620 36
1790692625 36
1790692630 36
1790692635 36
1790692640 36
1790692645 36
1790692650 36
1790692655 36
1790692660 48
1790692665 48
1790692670 48
1790692675 48
1790692680 48
1790692685 48
1790692690 48
1790692695 48
1790692700 48
1790692705 48
1790692710 48
1790692715 48
```
</details>

---

