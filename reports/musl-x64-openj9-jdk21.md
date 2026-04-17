---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-17 06:07:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 23-28 cores)</summary>

```
1776420211 27
1776420216 27
1776420221 27
1776420226 28
1776420231 28
1776420236 25
1776420241 25
1776420246 25
1776420251 25
1776420256 25
1776420261 25
1776420266 25
1776420271 23
1776420276 23
1776420281 25
1776420286 25
1776420291 25
1776420296 25
1776420301 25
1776420306 25
```
</details>

---

