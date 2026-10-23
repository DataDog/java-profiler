---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 09:29:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 12 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 80-86 cores)</summary>

```
1792761941 82
1792761946 82
1792761951 80
1792761956 80
1792761961 80
1792761966 80
1792761971 80
1792761976 80
1792761981 80
1792761986 80
1792761991 80
1792761996 80
1792762001 82
1792762006 82
1792762011 82
1792762016 84
1792762021 84
1792762026 84
1792762031 86
1792762036 86
```
</details>

---

