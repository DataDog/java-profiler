---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 04:41:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 9 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 39-74 cores)</summary>

```
1794389830 39
1794389835 39
1794389840 39
1794389845 39
1794389850 39
1794389855 74
1794389860 74
1794389865 74
1794389870 74
1794389875 74
1794389880 74
1794389885 74
1794389890 74
1794389895 74
1794389900 74
1794389905 74
1794389910 74
1794389915 74
1794389920 74
1794389925 74
```
</details>

---

