---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-04 05:47:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (5 unique values: 20-32 cores)</summary>

```
1791106985 30
1791106990 30
1791106995 32
1791107000 32
1791107005 32
1791107010 22
1791107015 22
1791107020 22
1791107025 22
1791107030 22
1791107035 22
1791107040 22
1791107045 22
1791107050 20
1791107055 20
1791107060 20
1791107065 20
1791107070 31
1791107075 31
1791107080 31
```
</details>

---

