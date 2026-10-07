---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-07 10:29:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 31-39 cores)</summary>

```
1791382926 39
1791382931 39
1791382936 39
1791382941 39
1791382946 39
1791382951 39
1791382956 39
1791382961 39
1791382966 39
1791382971 34
1791382976 34
1791382981 34
1791382986 34
1791382991 34
1791382996 34
1791383001 34
1791383006 34
1791383011 34
1791383016 34
1791383021 34
```
</details>

---

