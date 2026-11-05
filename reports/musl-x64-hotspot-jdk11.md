---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 07:17:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (4 unique values: 22-44 cores)</summary>

```
1793880775 40
1793880780 40
1793880785 40
1793880790 40
1793880795 40
1793880800 40
1793880805 40
1793880810 42
1793880815 42
1793880820 42
1793880825 42
1793880830 44
1793880835 44
1793880840 42
1793880845 42
1793880850 42
1793880855 42
1793880860 22
1793880865 22
1793880870 22
```
</details>

---

