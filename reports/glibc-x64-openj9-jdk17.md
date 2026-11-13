---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 09:34:13 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 71-74 cores)</summary>

```
1794580046 74
1794580051 74
1794580056 74
1794580061 74
1794580066 74
1794580071 74
1794580076 74
1794580081 73
1794580086 73
1794580091 73
1794580096 73
1794580101 71
1794580106 71
1794580111 71
1794580116 71
1794580121 71
1794580126 71
1794580131 71
1794580136 71
1794580141 71
```
</details>

---

