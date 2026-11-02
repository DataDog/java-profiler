---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 07:22:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1793621930 96
1793621935 96
1793621940 96
1793621945 96
1793621950 96
1793621955 96
1793621960 96
1793621965 96
1793621970 96
1793621975 96
1793621980 96
1793621985 96
1793621990 96
1793621995 96
1793622000 96
1793622005 96
1793622010 96
1793622015 96
1793622020 94
1793622025 94
```
</details>

---

