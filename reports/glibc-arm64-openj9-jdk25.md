---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:40:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794324953 48
1794324958 48
1794324963 48
1794324968 46
1794324973 46
1794324978 46
1794324983 46
1794324988 46
1794324993 46
1794324998 46
1794325003 46
1794325008 46
1794325013 46
1794325018 46
1794325023 46
1794325028 46
1794325033 46
1794325038 46
1794325043 46
1794325048 43
```
</details>

---

