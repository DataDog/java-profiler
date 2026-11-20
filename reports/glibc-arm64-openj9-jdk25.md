---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 12:12:24 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 14 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (3 unique values: 29-64 cores)</summary>

```
1795194468 49
1795194473 49
1795194478 49
1795194483 49
1795194488 49
1795194493 49
1795194498 49
1795194503 49
1795194508 49
1795194513 49
1795194518 49
1795194523 64
1795194528 64
1795194533 64
1795194538 64
1795194543 64
1795194548 64
1795194553 64
1795194558 64
1795194563 29
```
</details>

---

