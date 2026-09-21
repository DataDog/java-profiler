---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 00:47:24 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (5 unique values: 47-71 cores)</summary>

```
1789965818 48
1789965823 48
1789965828 57
1789965833 57
1789965838 47
1789965843 47
1789965848 47
1789965853 47
1789965858 47
1789965863 47
1789965868 47
1789965873 47
1789965878 47
1789965883 47
1789965888 47
1789965893 47
1789965898 47
1789965903 71
1789965908 71
1789965913 71
```
</details>

---

