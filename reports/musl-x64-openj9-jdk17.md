---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-15 14:59:48 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 880 |
| Sample Rate | 14.67/sec |
| Health Score | 917% |
| Threads | 12 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 75-83 cores)</summary>

```
1776279303 80
1776279308 80
1776279313 80
1776279318 80
1776279323 80
1776279328 80
1776279333 80
1776279338 83
1776279343 83
1776279348 80
1776279353 80
1776279358 80
1776279363 80
1776279368 80
1776279373 80
1776279378 80
1776279383 75
1776279388 75
1776279393 75
1776279398 75
```
</details>

---

