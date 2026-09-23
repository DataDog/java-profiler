---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:09:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 9 |
| Allocations | 133 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1790168695 40
1790168700 40
1790168705 40
1790168710 40
1790168715 40
1790168720 40
1790168725 45
1790168730 45
1790168735 45
1790168740 45
1790168745 45
1790168750 45
1790168755 45
1790168760 45
1790168765 45
1790168770 45
1790168776 45
1790168781 45
1790168786 45
1790168791 45
```
</details>

---

