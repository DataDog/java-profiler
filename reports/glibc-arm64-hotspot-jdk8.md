---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 05:58:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 34-49 cores)</summary>

```
1793789660 39
1793789665 39
1793789670 39
1793789675 39
1793789680 39
1793789685 39
1793789690 39
1793789695 39
1793789700 44
1793789705 44
1793789710 34
1793789715 34
1793789720 39
1793789725 39
1793789730 39
1793789735 36
1793789740 36
1793789745 36
1793789750 36
1793789755 36
```
</details>

---

