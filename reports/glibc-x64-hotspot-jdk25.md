---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 07:16:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786446592 43
1786446597 43
1786446602 48
1786446607 48
1786446612 48
1786446617 48
1786446622 48
1786446627 48
1786446632 48
1786446637 48
1786446642 48
1786446647 48
1786446652 48
1786446657 48
1786446662 48
1786446667 48
1786446672 48
1786446677 48
1786446682 48
1786446687 48
```
</details>

---

