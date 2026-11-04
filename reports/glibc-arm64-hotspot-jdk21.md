---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 05:58:31 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 49-51 cores)</summary>

```
1793789600 50
1793789605 50
1793789610 50
1793789615 50
1793789620 50
1793789625 50
1793789630 50
1793789635 50
1793789640 51
1793789645 51
1793789650 51
1793789655 51
1793789660 51
1793789665 51
1793789670 51
1793789675 51
1793789680 51
1793789685 49
1793789690 49
1793789695 49
```
</details>

---

