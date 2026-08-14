---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-14 01:01:24 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 37-45 cores)</summary>

```
1786683293 37
1786683298 37
1786683303 37
1786683308 37
1786683313 37
1786683318 37
1786683323 37
1786683328 37
1786683333 37
1786683338 37
1786683343 45
1786683348 45
1786683353 45
1786683358 45
1786683363 45
1786683368 45
1786683373 45
1786683378 45
1786683383 45
1786683388 45
```
</details>

---

