---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 17:57:55 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 12 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1793137952 96
1793137957 96
1793137962 96
1793137967 96
1793137972 96
1793137977 96
1793137982 96
1793137987 96
1793137992 94
1793137997 94
1793138002 94
1793138007 94
1793138012 94
1793138017 94
1793138022 94
1793138027 94
1793138032 94
1793138037 94
1793138042 94
1793138047 94
```
</details>

---

