---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 04:27:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1081 |
| Sample Rate | 18.02/sec |
| Health Score | 1126% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770110518 32
1770110523 32
1770110528 32
1770110533 32
1770110538 32
1770110543 32
1770110548 32
1770110553 32
1770110558 32
1770110563 32
1770110568 32
1770110573 32
1770110578 32
1770110583 32
1770110588 32
1770110593 32
1770110598 32
1770110603 32
1770110608 30
1770110613 30
```
</details>

---

