---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 12:07:23 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (4 unique values: 81-93 cores)</summary>

```
1794934933 86
1794934938 86
1794934943 83
1794934948 83
1794934953 83
1794934958 83
1794934964 83
1794934969 83
1794934974 83
1794934979 83
1794934984 81
1794934989 81
1794934994 81
1794934999 81
1794935004 81
1794935009 81
1794935014 81
1794935019 83
1794935024 83
1794935029 83
```
</details>

---

