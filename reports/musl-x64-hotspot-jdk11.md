---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:45:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 8 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (3 unique values: 49-79 cores)</summary>

```
1795642879 79
1795642884 79
1795642889 79
1795642894 79
1795642899 79
1795642904 79
1795642909 79
1795642914 79
1795642919 79
1795642924 79
1795642929 79
1795642934 79
1795642939 79
1795642944 79
1795642949 79
1795642954 79
1795642959 77
1795642964 77
1795642969 49
1795642974 49
```
</details>

---

