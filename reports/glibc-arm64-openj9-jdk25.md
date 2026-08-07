---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 08:27:33 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 16-19 cores)</summary>

```
1786105437 16
1786105442 16
1786105447 16
1786105452 16
1786105457 16
1786105462 16
1786105467 16
1786105472 16
1786105477 16
1786105482 19
1786105487 19
1786105492 19
1786105497 19
1786105502 19
1786105507 19
1786105512 19
1786105517 19
1786105522 19
1786105527 19
1786105532 19
```
</details>

---

