---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 09:09:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 9 |
| Allocations | 136 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 13 |

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
1790168775 45
1790168780 45
1790168785 45
1790168790 45
```
</details>

---

