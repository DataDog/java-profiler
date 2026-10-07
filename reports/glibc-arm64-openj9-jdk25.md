---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-07 07:29:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1791372335 39
1791372340 39
1791372345 39
1791372350 39
1791372355 39
1791372360 34
1791372365 34
1791372370 34
1791372375 34
1791372380 34
1791372385 34
1791372390 34
1791372395 34
1791372400 34
1791372405 34
1791372410 39
1791372415 39
1791372420 39
1791372425 39
1791372430 39
```
</details>

---

