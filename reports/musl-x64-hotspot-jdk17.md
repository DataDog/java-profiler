---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-01 06:31:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 845 |
| Sample Rate | 14.08/sec |
| Health Score | 880% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1790850457 29
1790850462 29
1790850467 29
1790850472 29
1790850477 29
1790850482 29
1790850487 29
1790850492 29
1790850497 29
1790850502 29
1790850507 29
1790850512 29
1790850517 29
1790850522 29
1790850527 29
1790850532 32
1790850537 32
1790850542 32
1790850548 32
1790850553 32
```
</details>

---

