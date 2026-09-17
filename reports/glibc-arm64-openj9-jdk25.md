---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:36:16 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 10 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789673437 48
1789673442 48
1789673447 48
1789673452 48
1789673457 48
1789673462 48
1789673467 48
1789673472 48
1789673477 48
1789673482 48
1789673487 48
1789673492 48
1789673497 48
1789673502 48
1789673507 48
1789673512 43
1789673517 43
1789673522 43
1789673527 43
1789673532 43
```
</details>

---

