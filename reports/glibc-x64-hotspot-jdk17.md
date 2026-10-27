---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-27 14:35:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 81-83 cores)</summary>

```
1793125801 83
1793125806 83
1793125811 83
1793125816 81
1793125821 81
1793125826 81
1793125831 81
1793125836 81
1793125841 83
1793125846 83
1793125851 83
1793125856 83
1793125861 83
1793125866 83
1793125871 83
1793125876 83
1793125881 83
1793125886 83
1793125891 83
1793125896 83
```
</details>

---

