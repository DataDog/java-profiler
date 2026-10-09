---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 03:39:36 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 46-56 cores)</summary>

```
1791531269 56
1791531274 56
1791531279 56
1791531284 56
1791531289 56
1791531294 56
1791531299 56
1791531304 56
1791531309 56
1791531314 56
1791531319 56
1791531324 54
1791531329 54
1791531334 54
1791531339 54
1791531344 54
1791531349 54
1791531354 46
1791531359 46
1791531364 46
```
</details>

---

