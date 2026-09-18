---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 12:42:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 11 |
| Allocations | 130 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 20-23 cores)</summary>

```
1789749417 20
1789749422 20
1789749427 20
1789749432 20
1789749437 20
1789749442 20
1789749447 23
1789749452 23
1789749457 23
1789749462 23
1789749467 23
1789749472 23
1789749477 23
1789749482 23
1789749487 23
1789749492 23
1789749497 23
1789749502 23
1789749507 23
1789749512 23
```
</details>

---

