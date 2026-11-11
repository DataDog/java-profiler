---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 19:35:12 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 834 |
| Sample Rate | 13.90/sec |
| Health Score | 869% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (5 unique values: 15-30 cores)</summary>

```
1794357041 26
1794357046 26
1794357051 28
1794357056 28
1794357061 28
1794357066 28
1794357071 28
1794357076 28
1794357081 30
1794357086 30
1794357091 30
1794357096 30
1794357101 30
1794357106 24
1794357111 24
1794357116 24
1794357121 24
1794357126 15
1794357131 15
1794357136 15
```
</details>

---

