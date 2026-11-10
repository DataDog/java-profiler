---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 15:03:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (7 unique values: 87-94 cores)</summary>

```
1794340522 93
1794340527 93
1794340532 93
1794340537 93
1794340542 93
1794340547 93
1794340552 93
1794340557 91
1794340562 91
1794340567 89
1794340572 89
1794340577 89
1794340582 89
1794340587 89
1794340592 89
1794340597 89
1794340602 92
1794340607 92
1794340612 90
1794340617 90
```
</details>

---

