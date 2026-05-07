---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 19:05:11 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 9 |
| Allocations | 428 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (6 unique values: 44-93 cores)</summary>

```
1778194841 48
1778194846 48
1778194851 49
1778194856 49
1778194861 49
1778194866 49
1778194871 49
1778194876 49
1778194881 49
1778194886 44
1778194891 44
1778194896 48
1778194901 48
1778194906 84
1778194911 84
1778194916 84
1778194921 84
1778194926 84
1778194931 84
1778194936 89
```
</details>

---

