---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-12 03:41:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 10 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 13 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 36-38 cores)</summary>

```
1773300954 36
1773300959 36
1773300964 36
1773300969 36
1773300974 36
1773300979 36
1773300984 38
1773300989 38
1773300994 38
1773300999 38
1773301004 38
1773301009 38
1773301014 38
1773301019 38
1773301024 38
1773301029 38
1773301034 38
1773301039 38
1773301044 38
1773301049 38
```
</details>

---

