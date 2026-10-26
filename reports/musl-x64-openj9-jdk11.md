---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 14:59:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 73-93 cores)</summary>

```
1793040906 91
1793040911 91
1793040916 91
1793040921 91
1793040926 91
1793040931 91
1793040936 91
1793040941 91
1793040946 91
1793040951 93
1793040956 93
1793040961 93
1793040966 73
1793040971 73
1793040976 73
1793040981 73
1793040986 73
1793040991 73
1793040996 73
1793041001 73
```
</details>

---

