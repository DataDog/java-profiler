---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 05:01:29 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (5 unique values: 69-80 cores)</summary>

```
1789721852 73
1789721857 73
1789721862 73
1789721867 73
1789721872 73
1789721877 73
1789721882 73
1789721887 73
1789721892 71
1789721897 71
1789721902 69
1789721907 69
1789721912 69
1789721917 69
1789721922 69
1789721927 73
1789721932 73
1789721937 73
1789721942 73
1789721947 73
```
</details>

---

