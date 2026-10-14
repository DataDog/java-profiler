---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-14 11:49:32 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 14 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1791992553 53
1791992558 53
1791992563 53
1791992568 48
1791992573 48
1791992578 48
1791992583 48
1791992588 48
1791992593 48
1791992598 48
1791992603 48
1791992608 48
1791992613 48
1791992618 48
1791992623 48
1791992628 53
1791992634 53
1791992639 53
1791992644 53
1791992649 53
```
</details>

---

