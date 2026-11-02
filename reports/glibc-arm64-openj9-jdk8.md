---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-02 13:05:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793642476 48
1793642481 48
1793642486 48
1793642491 48
1793642496 48
1793642501 48
1793642506 48
1793642511 48
1793642516 48
1793642521 48
1793642526 48
1793642531 48
1793642536 48
1793642541 48
1793642546 48
1793642551 48
1793642556 48
1793642561 48
1793642566 48
1793642571 48
```
</details>

---

