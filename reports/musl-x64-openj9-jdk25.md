---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 12:19:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 19.03/sec |
| Health Score | 1189% |
| Threads | 11 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 875 |
| Sample Rate | 29.17/sec |
| Health Score | 1823% |
| Threads | 13 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 58-69 cores)</summary>

```
1769706808 58
1769706813 58
1769706818 58
1769706823 58
1769706828 58
1769706833 58
1769706838 60
1769706843 60
1769706848 64
1769706853 64
1769706858 64
1769706863 64
1769706868 64
1769706873 64
1769706878 64
1769706883 64
1769706888 64
1769706893 64
1769706898 64
1769706903 64
```
</details>

---

