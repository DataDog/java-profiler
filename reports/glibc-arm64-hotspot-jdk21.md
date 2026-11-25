---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:02:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 9 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795618590 34
1795618595 34
1795618600 34
1795618605 34
1795618610 29
1795618615 29
1795618620 29
1795618625 29
1795618630 29
1795618635 29
1795618640 29
1795618645 29
1795618650 29
1795618655 29
1795618660 29
1795618665 29
1795618670 34
1795618675 34
1795618680 34
1795618685 34
```
</details>

---

