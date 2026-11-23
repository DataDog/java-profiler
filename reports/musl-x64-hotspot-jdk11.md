---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:46:05 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 10 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (4 unique values: 73-77 cores)</summary>

```
1795451813 76
1795451818 76
1795451823 77
1795451828 77
1795451833 73
1795451838 73
1795451843 73
1795451848 73
1795451853 73
1795451858 73
1795451863 73
1795451868 73
1795451873 75
1795451878 75
1795451883 75
1795451888 75
1795451893 75
1795451898 75
1795451903 75
1795451908 77
```
</details>

---

