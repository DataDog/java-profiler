---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:40:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (5 unique values: 34-39 cores)</summary>

```
1794324917 37
1794324922 37
1794324927 34
1794324932 34
1794324937 38
1794324942 38
1794324947 37
1794324952 37
1794324957 39
1794324963 39
1794324968 39
1794324973 36
1794324978 36
1794324983 36
1794324988 36
1794324993 36
1794324998 36
1794325003 36
1794325008 36
1794325013 37
```
</details>

---

