---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 04:44:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (5 unique values: 61-75 cores)</summary>

```
1795426788 75
1795426793 66
1795426798 66
1795426803 66
1795426808 66
1795426813 66
1795426818 66
1795426823 66
1795426828 64
1795426833 64
1795426838 64
1795426843 64
1795426848 64
1795426853 64
1795426858 64
1795426863 64
1795426868 62
1795426873 62
1795426878 62
1795426883 62
```
</details>

---

