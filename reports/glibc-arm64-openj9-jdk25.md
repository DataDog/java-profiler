---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 15:32:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 244 |
| Sample Rate | 4.07/sec |
| Health Score | 254% |
| Threads | 11 |
| Allocations | 165 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 313 |
| Sample Rate | 5.22/sec |
| Health Score | 326% |
| Threads | 16 |
| Allocations | 191 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1790018926 31
1790018931 31
1790018936 31
1790018941 31
1790018946 31
1790018951 31
1790018956 31
1790018961 31
1790018966 31
1790018971 36
1790018976 36
1790018981 36
1790018986 36
1790018991 36
1790018996 36
1790019001 36
1790019006 36
1790019011 36
1790019016 31
1790019021 31
```
</details>

---

