---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-22 11:31:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 50-61 cores)</summary>

```
1776871165 56
1776871170 56
1776871175 56
1776871180 61
1776871185 61
1776871190 61
1776871195 61
1776871200 61
1776871205 50
1776871210 50
1776871215 52
1776871220 52
1776871225 52
1776871230 52
1776871235 52
1776871240 52
1776871245 52
1776871250 52
1776871255 52
1776871260 52
```
</details>

---

