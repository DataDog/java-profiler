---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-12 20:17:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 40 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 12 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1786579989 44
1786579994 44
1786579999 44
1786580004 48
1786580009 48
1786580014 48
1786580019 48
1786580024 48
1786580029 48
1786580034 48
1786580039 48
1786580044 48
1786580049 48
1786580054 43
1786580059 43
1786580064 43
1786580069 43
1786580074 43
1786580079 43
1786580084 43
```
</details>

---

