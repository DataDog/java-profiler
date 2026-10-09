---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-09 05:55:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1791539430 40
1791539435 40
1791539440 40
1791539445 40
1791539450 40
1791539455 40
1791539460 40
1791539465 40
1791539470 40
1791539475 40
1791539480 48
1791539485 48
1791539490 48
1791539495 48
1791539500 48
1791539505 48
1791539510 48
1791539515 48
1791539520 48
1791539525 48
```
</details>

---

