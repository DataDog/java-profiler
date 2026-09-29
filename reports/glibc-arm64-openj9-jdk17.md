---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 10:43:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 14 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 28-36 cores)</summary>

```
1790692661 28
1790692666 28
1790692671 28
1790692676 28
1790692681 28
1790692686 28
1790692691 28
1790692696 36
1790692701 36
1790692706 36
1790692711 36
1790692716 36
1790692721 36
1790692726 36
1790692731 36
1790692736 36
1790692741 36
1790692746 36
1790692751 36
1790692756 36
```
</details>

---

