---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 17:02:39 EST

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
| CPU Cores (start) | 45 |
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
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1793829485 45
1793829490 45
1793829495 45
1793829500 45
1793829505 45
1793829510 45
1793829515 45
1793829520 45
1793829525 45
1793829530 48
1793829535 48
1793829540 48
1793829545 48
1793829550 48
1793829555 48
1793829560 48
1793829565 48
1793829571 48
1793829576 48
1793829581 48
```
</details>

---

