---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 15:22:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 67-75 cores)</summary>

```
1794428220 75
1794428225 75
1794428230 75
1794428235 75
1794428240 75
1794428245 67
1794428250 67
1794428255 67
1794428260 67
1794428265 67
1794428270 67
1794428275 67
1794428280 67
1794428285 67
1794428290 67
1794428295 67
1794428300 67
1794428305 69
1794428310 69
1794428315 69
```
</details>

---

