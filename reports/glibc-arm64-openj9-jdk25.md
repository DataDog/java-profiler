---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-02 11:44:46 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788363483 64
1788363488 64
1788363493 64
1788363498 64
1788363503 64
1788363508 64
1788363513 64
1788363518 64
1788363523 64
1788363528 64
1788363533 64
1788363538 64
1788363543 64
1788363548 64
1788363553 64
1788363558 64
1788363563 64
1788363568 64
1788363573 64
1788363578 64
```
</details>

---

