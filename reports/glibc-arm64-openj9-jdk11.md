---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 11:01:29 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 909 |
| Sample Rate | 15.15/sec |
| Health Score | 947% |
| Threads | 9 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1794585456 40
1794585461 40
1794585466 40
1794585471 40
1794585476 40
1794585481 40
1794585486 40
1794585491 40
1794585496 40
1794585501 40
1794585506 48
1794585511 48
1794585517 48
1794585522 48
1794585527 48
1794585532 48
1794585537 48
1794585542 48
1794585547 48
1794585552 48
```
</details>

---

