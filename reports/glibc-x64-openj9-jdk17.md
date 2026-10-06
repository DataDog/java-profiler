---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-06 10:08:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 8 |
| Allocations | 296 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 10 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1791295360 28
1791295365 28
1791295370 28
1791295375 28
1791295380 28
1791295385 28
1791295390 28
1791295395 30
1791295400 30
1791295405 30
1791295410 30
1791295415 30
1791295420 30
1791295425 30
1791295430 30
1791295435 28
1791295440 28
1791295445 28
1791295450 28
1791295455 28
```
</details>

---

