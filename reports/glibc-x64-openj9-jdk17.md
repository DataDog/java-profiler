---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-09 06:39:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 9 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1794224101 29
1794224106 29
1794224111 29
1794224116 29
1794224121 29
1794224126 29
1794224131 29
1794224136 29
1794224141 29
1794224146 29
1794224151 29
1794224156 32
1794224161 32
1794224166 30
1794224171 30
1794224176 30
1794224181 30
1794224186 30
1794224191 30
1794224196 30
```
</details>

---

