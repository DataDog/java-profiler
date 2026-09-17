---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 15:36:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1789673426 32
1789673431 32
1789673436 32
1789673441 32
1789673446 32
1789673451 32
1789673456 32
1789673462 32
1789673467 32
1789673472 32
1789673477 32
1789673482 32
1789673487 32
1789673492 32
1789673497 32
1789673502 32
1789673507 12
1789673512 12
1789673517 12
1789673522 12
```
</details>

---

