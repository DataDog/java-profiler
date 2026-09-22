---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 07:06:13 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 428 |
| Sample Rate | 7.13/sec |
| Health Score | 446% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1790074849 96
1790074854 96
1790074859 96
1790074864 94
1790074869 94
1790074874 94
1790074879 94
1790074884 94
1790074889 94
1790074894 94
1790074899 94
1790074904 94
1790074909 94
1790074914 94
1790074919 94
1790074924 94
1790074929 94
1790074934 94
1790074939 96
1790074944 96
```
</details>

---

