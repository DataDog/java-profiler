---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 06:26:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 870 |
| Sample Rate | 14.50/sec |
| Health Score | 906% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (4 unique values: 67-77 cores)</summary>

```
1786357291 68
1786357296 68
1786357301 67
1786357306 67
1786357311 67
1786357316 67
1786357321 67
1786357326 67
1786357331 67
1786357336 67
1786357342 67
1786357347 75
1786357352 75
1786357357 75
1786357362 75
1786357367 75
1786357372 75
1786357377 75
1786357382 75
1786357387 75
```
</details>

---

