---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-21 00:47:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 80-81 cores)</summary>

```
1789965823 80
1789965828 80
1789965833 80
1789965838 80
1789965843 80
1789965848 80
1789965853 80
1789965858 80
1789965863 80
1789965868 80
1789965873 80
1789965878 80
1789965883 80
1789965888 80
1789965893 81
1789965898 81
1789965903 81
1789965908 81
1789965913 81
1789965918 81
```
</details>

---

