---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-04 05:47:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 11 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791107000 48
1791107005 48
1791107010 43
1791107015 43
1791107020 43
1791107025 43
1791107030 43
1791107035 43
1791107040 43
1791107045 43
1791107050 48
1791107055 48
1791107060 48
1791107065 48
1791107070 48
1791107075 48
1791107080 48
1791107085 48
1791107090 48
1791107095 48
```
</details>

---

