---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 15:36:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 10 |
| Allocations | 185 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789673437 43
1789673442 38
1789673447 38
1789673452 38
1789673457 38
1789673462 38
1789673467 38
1789673472 38
1789673477 38
1789673482 38
1789673487 38
1789673492 38
1789673497 38
1789673502 38
1789673507 48
1789673512 48
1789673517 48
1789673522 48
1789673527 48
1789673532 48
```
</details>

---

