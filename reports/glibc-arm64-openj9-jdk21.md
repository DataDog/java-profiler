---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 08:46:37 EDT

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
| CPU Cores (start) | 8 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 8-43 cores)</summary>

```
1792672929 8
1792672934 8
1792672939 8
1792672944 8
1792672949 8
1792672954 8
1792672959 8
1792672964 8
1792672969 8
1792672974 8
1792672979 8
1792672984 8
1792672989 8
1792672994 13
1792672999 13
1792673004 43
1792673009 43
1792673014 43
1792673019 43
1792673024 43
```
</details>

---

