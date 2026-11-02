---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 08:53:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (5 unique values: 38-45 cores)</summary>

```
1793627316 38
1793627321 40
1793627326 40
1793627331 45
1793627336 45
1793627341 45
1793627346 45
1793627351 45
1793627356 45
1793627361 45
1793627366 45
1793627371 45
1793627376 45
1793627381 44
1793627386 44
1793627391 44
1793627396 44
1793627401 44
1793627406 44
1793627411 44
```
</details>

---

