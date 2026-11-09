---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 06:39:12 EST

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
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1001 |
| Sample Rate | 16.68/sec |
| Health Score | 1042% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1794224071 91
1794224076 91
1794224081 91
1794224086 93
1794224091 93
1794224096 93
1794224101 93
1794224106 93
1794224111 93
1794224116 93
1794224121 93
1794224126 93
1794224131 93
1794224136 93
1794224141 93
1794224146 93
1794224151 93
1794224156 93
1794224161 93
1794224166 93
```
</details>

---

