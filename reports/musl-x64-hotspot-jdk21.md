---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 07:41:13 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 54-75 cores)</summary>

```
1794487020 54
1794487025 56
1794487030 56
1794487035 56
1794487040 56
1794487045 56
1794487050 56
1794487055 56
1794487060 58
1794487065 58
1794487070 75
1794487075 75
1794487080 75
1794487085 75
1794487090 75
1794487095 75
1794487100 75
1794487105 75
1794487110 72
1794487115 72
```
</details>

---

