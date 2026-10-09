---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 03:39:36 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 92 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 26-35 cores)</summary>

```
1791531254 35
1791531259 35
1791531264 35
1791531269 35
1791531274 35
1791531279 35
1791531284 35
1791531289 35
1791531294 35
1791531299 35
1791531304 35
1791531309 35
1791531314 35
1791531319 31
1791531324 31
1791531329 29
1791531334 29
1791531339 29
1791531344 29
1791531349 29
```
</details>

---

