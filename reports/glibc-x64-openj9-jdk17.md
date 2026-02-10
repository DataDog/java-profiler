---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-10 16:50:46 EST

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
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 10 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 925 |
| Sample Rate | 15.42/sec |
| Health Score | 964% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1770759991 59
1770759996 59
1770760001 59
1770760006 59
1770760011 59
1770760016 59
1770760021 59
1770760026 59
1770760031 59
1770760036 59
1770760041 59
1770760046 59
1770760051 59
1770760056 59
1770760061 61
1770760066 61
1770760071 61
1770760076 61
1770760081 61
1770760086 61
```
</details>

---

