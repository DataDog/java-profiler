---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 08:03:27 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 26-71 cores)</summary>

```
1789991847 26
1789991852 48
1789991857 48
1789991862 48
1789991867 48
1789991872 48
1789991877 48
1789991882 48
1789991887 48
1789991892 71
1789991897 71
1789991902 71
1789991907 71
1789991912 71
1789991917 71
1789991922 71
1789991927 71
1789991932 71
1789991937 71
1789991942 71
```
</details>

---

