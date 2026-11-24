---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 09:47:30 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 13 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795531368 33
1795531373 33
1795531378 33
1795531383 33
1795531388 33
1795531393 33
1795531398 33
1795531403 33
1795531408 33
1795531413 33
1795531418 33
1795531423 33
1795531428 33
1795531433 33
1795531438 33
1795531443 33
1795531448 33
1795531453 33
1795531458 33
1795531463 33
```
</details>

---

