---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 04:41:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 418 |

<details>
<summary>CPU Timeline (4 unique values: 84-89 cores)</summary>

```
1794389840 89
1794389845 89
1794389850 89
1794389855 89
1794389860 89
1794389865 89
1794389870 84
1794389875 84
1794389880 84
1794389885 84
1794389890 84
1794389895 84
1794389900 84
1794389905 86
1794389910 86
1794389915 88
1794389920 88
1794389925 88
1794389930 88
1794389935 86
```
</details>

---

