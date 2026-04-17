---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-17 10:21:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 809 |
| Sample Rate | 13.48/sec |
| Health Score | 842% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (4 unique values: 50-55 cores)</summary>

```
1776435107 51
1776435112 51
1776435117 51
1776435122 51
1776435127 51
1776435132 51
1776435137 51
1776435142 53
1776435147 53
1776435152 53
1776435157 55
1776435162 55
1776435167 55
1776435172 55
1776435177 55
1776435182 55
1776435187 50
1776435192 50
1776435197 50
1776435202 50
```
</details>

---

