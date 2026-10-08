---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-08 12:33:20 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 46-59 cores)</summary>

```
1791476937 51
1791476942 51
1791476947 51
1791476952 51
1791476957 51
1791476962 51
1791476967 51
1791476972 51
1791476977 51
1791476982 51
1791476987 51
1791476992 51
1791476997 46
1791477002 46
1791477007 46
1791477012 46
1791477017 46
1791477022 46
1791477028 46
1791477033 46
```
</details>

---

