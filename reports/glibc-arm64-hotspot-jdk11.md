---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-14 08:33:42 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 324 |
| Sample Rate | 5.40/sec |
| Health Score | 338% |
| Threads | 11 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1791980950 48
1791980955 48
1791980960 48
1791980965 48
1791980970 48
1791980975 48
1791980980 48
1791980985 48
1791980990 48
1791980995 48
1791981000 48
1791981005 48
1791981010 48
1791981015 48
1791981020 48
1791981025 48
1791981030 48
1791981035 48
1791981040 48
1791981045 48
```
</details>

---

