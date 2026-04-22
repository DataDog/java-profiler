---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-22 11:31:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1776871170 29
1776871175 29
1776871180 29
1776871185 29
1776871190 29
1776871195 26
1776871200 26
1776871205 30
1776871210 30
1776871215 30
1776871220 30
1776871225 30
1776871230 30
1776871235 26
1776871240 26
1776871245 26
1776871250 26
1776871255 26
1776871260 26
1776871265 26
```
</details>

---

