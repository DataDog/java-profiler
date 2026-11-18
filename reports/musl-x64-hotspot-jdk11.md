---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 07:14:56 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 43-53 cores)</summary>

```
1795003828 53
1795003833 53
1795003838 53
1795003843 51
1795003848 51
1795003853 51
1795003858 51
1795003863 51
1795003868 51
1795003873 51
1795003878 51
1795003883 51
1795003888 51
1795003893 51
1795003898 51
1795003903 51
1795003908 51
1795003913 51
1795003918 51
1795003923 51
```
</details>

---

