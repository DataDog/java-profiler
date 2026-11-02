---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 07:22:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 60-77 cores)</summary>

```
1793621935 60
1793621940 60
1793621945 60
1793621950 75
1793621955 75
1793621960 75
1793621965 75
1793621970 75
1793621975 77
1793621980 77
1793621985 77
1793621990 77
1793621995 77
1793622000 77
1793622005 77
1793622010 77
1793622015 77
1793622020 77
1793622025 77
1793622030 77
```
</details>

---

