---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:24:09 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 9 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 31-48 cores)</summary>

```
1794831602 31
1794831607 31
1794831612 31
1794831617 31
1794831622 31
1794831627 31
1794831632 31
1794831637 31
1794831642 36
1794831647 36
1794831652 36
1794831657 36
1794831662 36
1794831667 36
1794831672 31
1794831677 31
1794831682 31
1794831687 31
1794831692 31
1794831697 31
```
</details>

---

