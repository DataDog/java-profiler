---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 13:29:13 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 8 |
| Allocations | 440 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 24-32 cores)</summary>

```
1794939880 30
1794939885 30
1794939890 30
1794939895 30
1794939901 30
1794939906 30
1794939911 30
1794939916 30
1794939921 30
1794939926 30
1794939931 30
1794939936 30
1794939941 30
1794939946 30
1794939951 30
1794939956 32
1794939961 32
1794939966 32
1794939971 32
1794939976 24
```
</details>

---

