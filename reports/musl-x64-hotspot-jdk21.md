---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 14:34:11 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 14.10/sec |
| Health Score | 881% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 86-94 cores)</summary>

```
1793125625 92
1793125630 92
1793125635 92
1793125640 92
1793125645 92
1793125650 94
1793125655 94
1793125660 94
1793125665 94
1793125670 94
1793125675 94
1793125680 94
1793125685 86
1793125690 86
1793125695 86
1793125700 88
1793125705 88
1793125710 88
1793125715 88
1793125720 88
```
</details>

---

