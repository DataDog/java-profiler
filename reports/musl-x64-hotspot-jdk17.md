---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-12 06:37:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 8 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 8-22 cores)</summary>

```
1770895940 8
1770895945 8
1770895950 8
1770895955 8
1770895960 8
1770895965 8
1770895970 8
1770895975 8
1770895980 8
1770895985 8
1770895990 8
1770895995 15
1770896000 15
1770896005 13
1770896010 13
1770896015 20
1770896020 20
1770896025 20
1770896030 20
1770896035 20
```
</details>

---

