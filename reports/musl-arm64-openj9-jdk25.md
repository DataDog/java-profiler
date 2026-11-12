---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 12:07:09 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 13 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 14 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1794502921 41
1794502926 41
1794502931 46
1794502936 46
1794502941 46
1794502946 46
1794502951 46
1794502956 46
1794502961 46
1794502966 46
1794502971 46
1794502976 46
1794502981 51
1794502986 51
1794502991 51
1794502996 51
1794503001 51
1794503006 51
1794503011 51
1794503016 51
```
</details>

---

