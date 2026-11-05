---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 19:07:42 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 14 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793836976 30
1793836981 30
1793836986 30
1793836991 30
1793836996 30
1793837001 30
1793837006 30
1793837011 30
1793837016 30
1793837021 30
1793837026 30
1793837031 30
1793837036 30
1793837041 30
1793837046 30
1793837051 30
1793837056 30
1793837061 30
1793837066 30
1793837071 30
```
</details>

---

