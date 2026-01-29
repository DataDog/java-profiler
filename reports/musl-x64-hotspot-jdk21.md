---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-29 12:19:51 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 17.43/sec |
| Health Score | 1089% |
| Threads | 11 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 26.27/sec |
| Health Score | 1642% |
| Threads | 12 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 17-39 cores)</summary>

```
1769706803 39
1769706808 39
1769706813 39
1769706818 39
1769706823 39
1769706828 39
1769706833 39
1769706838 39
1769706843 39
1769706848 39
1769706853 39
1769706858 37
1769706863 37
1769706868 17
1769706873 17
1769706878 37
1769706883 37
1769706888 36
1769706893 36
1769706898 36
```
</details>

---

