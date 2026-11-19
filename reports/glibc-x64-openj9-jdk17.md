---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 05:46:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 56-59 cores)</summary>

```
1795084995 59
1795085000 59
1795085005 59
1795085010 59
1795085015 56
1795085020 56
1795085025 56
1795085030 56
1795085035 56
1795085040 56
1795085045 56
1795085050 56
1795085055 56
1795085060 56
1795085065 56
1795085070 56
1795085075 56
1795085080 56
1795085085 56
1795085090 56
```
</details>

---

