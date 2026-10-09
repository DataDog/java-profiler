---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 03:39:37 EDT

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
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 322 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (5 unique values: 41-91 cores)</summary>

```
1791531239 59
1791531244 59
1791531249 59
1791531254 61
1791531259 61
1791531264 61
1791531269 91
1791531274 91
1791531279 91
1791531284 91
1791531289 91
1791531294 91
1791531299 58
1791531304 58
1791531309 58
1791531314 58
1791531319 58
1791531324 58
1791531329 58
1791531334 58
```
</details>

---

