---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 13:05:33 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1793642466 36
1793642471 36
1793642476 36
1793642481 36
1793642486 36
1793642491 36
1793642496 36
1793642501 36
1793642506 36
1793642511 36
1793642516 36
1793642521 36
1793642526 36
1793642531 36
1793642536 36
1793642541 36
1793642546 36
1793642551 36
1793642556 36
1793642561 36
```
</details>

---

