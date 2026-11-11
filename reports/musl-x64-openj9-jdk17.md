---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 19:35:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 76-85 cores)</summary>

```
1794357041 85
1794357046 85
1794357051 85
1794357056 85
1794357061 85
1794357066 85
1794357071 85
1794357076 85
1794357081 83
1794357086 83
1794357091 85
1794357096 85
1794357101 85
1794357106 85
1794357111 85
1794357116 85
1794357121 85
1794357126 85
1794357131 85
1794357136 76
```
</details>

---

