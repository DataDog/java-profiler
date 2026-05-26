---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-26 06:26:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (6 unique values: 43-65 cores)</summary>

```
1779790895 52
1779790900 48
1779790905 48
1779790910 43
1779790915 43
1779790920 60
1779790925 60
1779790930 65
1779790935 65
1779790940 65
1779790945 65
1779790950 65
1779790955 65
1779790960 65
1779790965 61
1779790970 61
1779790975 61
1779790980 61
1779790985 61
1779790990 61
```
</details>

---

