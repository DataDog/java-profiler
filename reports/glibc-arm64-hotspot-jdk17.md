---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-26 07:12:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 15 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787742489 64
1787742494 64
1787742499 64
1787742504 64
1787742509 64
1787742514 64
1787742519 64
1787742524 64
1787742529 64
1787742534 64
1787742539 64
1787742544 64
1787742549 64
1787742554 64
1787742559 64
1787742564 64
1787742569 64
1787742574 64
1787742579 64
1787742584 64
```
</details>

---

