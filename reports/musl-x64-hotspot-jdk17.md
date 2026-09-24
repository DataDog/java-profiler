---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 04:39:31 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (3 unique values: 43-53 cores)</summary>

```
1790238952 43
1790238957 43
1790238962 51
1790238967 51
1790238972 51
1790238978 51
1790238983 51
1790238988 51
1790238993 51
1790238998 51
1790239003 53
1790239008 53
1790239013 53
1790239018 53
1790239023 53
1790239028 53
1790239033 53
1790239038 53
1790239043 53
1790239048 53
```
</details>

---

