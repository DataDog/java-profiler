---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-03 05:48:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 44-81 cores)</summary>

```
1791020617 81
1791020622 81
1791020627 81
1791020632 48
1791020637 48
1791020642 48
1791020647 48
1791020652 48
1791020657 48
1791020662 48
1791020667 48
1791020672 48
1791020677 48
1791020682 48
1791020687 48
1791020692 48
1791020697 48
1791020702 48
1791020707 48
1791020712 46
```
</details>

---

