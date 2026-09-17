---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 15:36:17 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 9 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789673447 48
1789673452 48
1789673457 48
1789673462 48
1789673467 48
1789673472 48
1789673477 48
1789673482 48
1789673487 48
1789673492 46
1789673497 46
1789673502 46
1789673507 46
1789673512 46
1789673517 46
1789673522 46
1789673527 46
1789673532 48
1789673537 48
1789673542 48
```
</details>

---

