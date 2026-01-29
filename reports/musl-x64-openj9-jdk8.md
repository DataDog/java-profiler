---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-01-29 06:14:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 76-87 cores)</summary>

```
1769684921 83
1769684926 83
1769684931 83
1769684936 78
1769684941 78
1769684946 78
1769684951 76
1769684956 76
1769684961 78
1769684966 78
1769684971 78
1769684976 87
1769684981 87
1769684986 84
1769684991 84
1769684996 84
1769685001 82
1769685006 82
1769685011 84
1769685016 84
```
</details>

---

