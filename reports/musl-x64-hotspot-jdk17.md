---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-04 05:47:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (5 unique values: 46-83 cores)</summary>

```
1791106985 83
1791106990 46
1791106995 46
1791107000 48
1791107005 48
1791107010 48
1791107015 48
1791107020 59
1791107025 59
1791107030 59
1791107035 59
1791107040 59
1791107045 59
1791107050 57
1791107055 57
1791107060 57
1791107065 57
1791107070 57
1791107075 57
1791107080 57
```
</details>

---

