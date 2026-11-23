---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:39:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 55-64 cores)</summary>

```
1795451617 64
1795451622 64
1795451627 64
1795451632 64
1795451637 55
1795451642 55
1795451647 55
1795451652 55
1795451657 55
1795451662 55
1795451667 55
1795451672 55
1795451677 55
1795451682 55
1795451687 55
1795451692 55
1795451697 60
1795451702 60
1795451707 55
1795451712 55
```
</details>

---

