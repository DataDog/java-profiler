---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 07:56:32 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 74-81 cores)</summary>

```
1786103547 81
1786103552 81
1786103557 81
1786103562 81
1786103567 81
1786103572 78
1786103577 78
1786103582 78
1786103587 78
1786103592 78
1786103597 78
1786103602 78
1786103607 76
1786103612 76
1786103617 76
1786103622 76
1786103627 76
1786103632 76
1786103637 76
1786103643 76
```
</details>

---

