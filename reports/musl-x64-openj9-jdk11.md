---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 18:10:54 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 557 |

<details>
<summary>CPU Timeline (2 unique values: 48-51 cores)</summary>

```
1795129575 48
1795129580 48
1795129585 48
1795129590 48
1795129595 48
1795129600 48
1795129605 48
1795129610 48
1795129615 48
1795129620 48
1795129625 48
1795129630 48
1795129635 48
1795129640 48
1795129645 51
1795129650 51
1795129655 51
1795129660 51
1795129665 51
1795129670 51
```
</details>

---

