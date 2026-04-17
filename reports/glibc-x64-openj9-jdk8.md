---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-17 10:21:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1776435071 30
1776435076 30
1776435081 32
1776435086 32
1776435091 32
1776435096 32
1776435101 32
1776435106 32
1776435111 32
1776435116 32
1776435121 29
1776435126 29
1776435131 29
1776435137 29
1776435142 29
1776435147 29
1776435152 29
1776435157 29
1776435162 29
1776435167 29
```
</details>

---

