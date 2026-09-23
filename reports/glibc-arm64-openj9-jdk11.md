---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:27:21 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (4 unique values: 39-48 cores)</summary>

```
1790173259 39
1790173264 39
1790173269 39
1790173275 39
1790173280 39
1790173285 39
1790173290 39
1790173295 39
1790173300 44
1790173305 44
1790173310 44
1790173315 46
1790173320 46
1790173325 46
1790173330 46
1790173335 46
1790173340 46
1790173345 46
1790173350 46
1790173355 48
```
</details>

---

