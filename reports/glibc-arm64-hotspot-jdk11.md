---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 08:27:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 19-32 cores)</summary>

```
1786105437 19
1786105442 19
1786105447 19
1786105452 27
1786105457 27
1786105462 27
1786105467 27
1786105472 27
1786105477 27
1786105482 27
1786105487 27
1786105492 27
1786105497 27
1786105502 27
1786105507 27
1786105512 32
1786105517 32
1786105522 32
1786105527 32
1786105532 32
```
</details>

---

