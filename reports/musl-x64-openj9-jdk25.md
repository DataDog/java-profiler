---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-22 11:31:59 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 80-85 cores)</summary>

```
1776871165 85
1776871170 85
1776871175 85
1776871180 80
1776871185 80
1776871190 80
1776871195 80
1776871200 80
1776871205 80
1776871210 80
1776871215 80
1776871220 80
1776871225 80
1776871230 80
1776871235 80
1776871240 80
1776871245 80
1776871250 80
1776871255 80
1776871260 80
```
</details>

---

