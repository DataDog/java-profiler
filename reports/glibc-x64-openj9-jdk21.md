---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:01:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1789743387 32
1789743392 32
1789743397 32
1789743402 32
1789743407 32
1789743412 32
1789743417 32
1789743422 32
1789743427 32
1789743432 32
1789743437 32
1789743442 32
1789743447 32
1789743452 32
1789743457 32
1789743462 32
1789743467 32
1789743472 32
1789743477 32
1789743482 32
```
</details>

---

