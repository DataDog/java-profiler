---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 12:37:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 820 |
| Sample Rate | 13.67/sec |
| Health Score | 854% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1794850050 81
1794850055 81
1794850060 81
1794850065 81
1794850070 81
1794850075 81
1794850080 81
1794850085 81
1794850090 77
1794850095 77
1794850100 77
1794850105 77
1794850110 77
1794850115 77
1794850120 77
1794850125 77
1794850130 77
1794850135 77
1794850140 77
1794850145 77
```
</details>

---

