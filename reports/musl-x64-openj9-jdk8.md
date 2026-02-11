---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-02-11 11:59:20 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 71-83 cores)</summary>

```
1770828944 80
1770828949 83
1770828954 83
1770828959 83
1770828964 83
1770828969 83
1770828974 83
1770828979 83
1770828984 83
1770828989 83
1770828994 83
1770828999 74
1770829004 74
1770829009 74
1770829014 74
1770829019 74
1770829024 74
1770829029 74
1770829034 74
1770829039 76
```
</details>

---

