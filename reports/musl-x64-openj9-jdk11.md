---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-22 07:19:27 EDT

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
| CPU Cores (start) | 7 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 7-25 cores)</summary>

```
1776856165 7
1776856170 7
1776856175 7
1776856180 7
1776856185 7
1776856190 7
1776856195 7
1776856200 7
1776856205 25
1776856210 25
1776856215 25
1776856220 25
1776856225 25
1776856230 25
1776856235 10
1776856240 10
1776856245 10
1776856250 10
1776856255 10
1776856260 10
```
</details>

---

