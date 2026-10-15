---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-15 12:04:42 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1792079959 73
1792079964 73
1792079969 73
1792079974 73
1792079979 73
1792079984 73
1792079989 73
1792079994 71
1792079999 71
1792080004 71
1792080009 71
1792080014 71
1792080019 71
1792080024 73
1792080029 73
1792080034 73
1792080039 73
1792080044 73
1792080049 73
1792080054 73
```
</details>

---

