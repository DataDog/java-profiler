---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-30 14:54:49 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 34-64 cores)</summary>

```
1777575025 40
1777575030 40
1777575035 40
1777575040 40
1777575045 40
1777575050 40
1777575055 40
1777575060 40
1777575065 40
1777575070 40
1777575075 40
1777575080 40
1777575085 40
1777575090 64
1777575095 64
1777575100 64
1777575105 34
1777575110 34
1777575115 34
1777575120 34
```
</details>

---

