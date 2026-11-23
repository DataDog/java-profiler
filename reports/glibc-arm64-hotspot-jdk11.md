---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:39:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 11 |
| Allocations | 185 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 54-58 cores)</summary>

```
1795451617 54
1795451622 54
1795451627 54
1795451632 54
1795451637 55
1795451642 55
1795451647 55
1795451652 55
1795451657 55
1795451662 55
1795451667 55
1795451672 55
1795451677 58
1795451682 58
1795451687 58
1795451692 58
1795451697 58
1795451702 55
1795451707 55
1795451712 55
```
</details>

---

