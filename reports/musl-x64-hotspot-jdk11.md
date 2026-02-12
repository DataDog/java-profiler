---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-12 06:37:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 849 |
| Sample Rate | 14.15/sec |
| Health Score | 884% |
| Threads | 12 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 87-91 cores)</summary>

```
1770895940 87
1770895945 87
1770895950 87
1770895955 87
1770895960 87
1770895965 91
1770895970 91
1770895975 91
1770895980 91
1770895985 91
1770895990 91
1770895995 91
1770896000 91
1770896005 91
1770896010 91
1770896015 91
1770896020 91
1770896025 91
1770896030 91
1770896035 91
```
</details>

---

