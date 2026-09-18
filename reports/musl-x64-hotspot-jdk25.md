---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:49:59 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (6 unique values: 51-58 cores)</summary>

```
1789731874 56
1789731879 54
1789731884 54
1789731889 58
1789731894 58
1789731899 58
1789731904 58
1789731909 58
1789731914 53
1789731919 53
1789731924 53
1789731929 53
1789731934 55
1789731939 55
1789731944 55
1789731949 53
1789731954 53
1789731959 53
1789731964 53
1789731969 53
```
</details>

---

