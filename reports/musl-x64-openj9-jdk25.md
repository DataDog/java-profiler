---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-08 12:33:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 10 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 14.10/sec |
| Health Score | 881% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1791476911 96
1791476916 96
1791476921 96
1791476926 96
1791476931 96
1791476936 96
1791476941 96
1791476946 96
1791476951 94
1791476956 94
1791476961 94
1791476966 94
1791476971 94
1791476976 94
1791476981 94
1791476986 96
1791476991 96
1791476996 94
1791477001 94
1791477006 94
```
</details>

---

