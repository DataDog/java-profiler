---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 14:55:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1788547840 48
1788547845 48
1788547850 48
1788547855 48
1788547860 43
1788547865 43
1788547870 38
1788547875 38
1788547880 38
1788547885 38
1788547890 38
1788547895 43
1788547900 43
1788547905 38
1788547910 38
1788547915 43
1788547920 43
1788547925 43
1788547930 43
1788547935 43
```
</details>

---

