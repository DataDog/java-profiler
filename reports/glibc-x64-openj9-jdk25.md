---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 10:54:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 64-92 cores)</summary>

```
1778165308 64
1778165313 64
1778165318 64
1778165323 64
1778165328 64
1778165333 64
1778165338 64
1778165343 78
1778165348 78
1778165353 78
1778165358 78
1778165363 78
1778165368 90
1778165373 90
1778165378 90
1778165383 90
1778165388 92
1778165393 92
1778165398 92
1778165403 92
```
</details>

---

