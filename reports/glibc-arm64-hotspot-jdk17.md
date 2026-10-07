---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-07 01:04:07 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 10 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 11 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791349050 43
1791349055 43
1791349060 43
1791349065 43
1791349070 43
1791349075 43
1791349080 43
1791349085 43
1791349090 43
1791349095 43
1791349100 43
1791349105 43
1791349110 48
1791349115 48
1791349120 48
1791349125 48
1791349130 48
1791349135 48
1791349140 48
1791349145 48
```
</details>

---

