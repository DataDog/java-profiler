---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 19:05:11 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (6 unique values: 44-93 cores)</summary>

```
1778194845 48
1778194850 49
1778194855 49
1778194860 49
1778194865 49
1778194870 49
1778194875 44
1778194880 44
1778194885 44
1778194890 44
1778194895 48
1778194900 48
1778194905 84
1778194910 84
1778194915 84
1778194920 84
1778194925 84
1778194930 84
1778194935 84
1778194940 89
```
</details>

---

