---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 13:04:55 EST

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
| CPU Cores (start) | 6 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 8 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 6-11 cores)</summary>

```
1794851930 6
1794851935 6
1794851940 6
1794851945 6
1794851950 6
1794851955 6
1794851960 6
1794851965 6
1794851970 6
1794851975 6
1794851980 6
1794851985 6
1794851990 6
1794851995 6
1794852000 6
1794852005 6
1794852010 11
1794852015 11
1794852020 11
1794852025 11
```
</details>

---

