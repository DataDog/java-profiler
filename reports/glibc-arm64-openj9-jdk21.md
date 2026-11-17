---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 14:02:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1794941945 38
1794941950 38
1794941955 38
1794941960 38
1794941965 38
1794941970 38
1794941975 38
1794941980 38
1794941985 38
1794941990 38
1794941995 38
1794942000 51
1794942005 51
1794942010 51
1794942015 51
1794942020 51
1794942025 51
1794942030 51
1794942035 51
1794942040 51
```
</details>

---

