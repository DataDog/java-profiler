---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 04:41:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 9 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794389820 94
1794389825 94
1794389830 94
1794389835 94
1794389840 94
1794389845 94
1794389850 94
1794389855 94
1794389860 94
1794389865 94
1794389870 96
1794389875 96
1794389880 96
1794389885 96
1794389890 96
1794389895 96
1794389900 96
1794389905 96
1794389910 96
1794389915 96
```
</details>

---

