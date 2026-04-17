---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-17 06:07:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 337 |
| Sample Rate | 5.62/sec |
| Health Score | 351% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1776420209 27
1776420214 27
1776420219 27
1776420224 27
1776420229 27
1776420234 27
1776420239 27
1776420244 27
1776420249 27
1776420254 27
1776420259 27
1776420264 27
1776420269 27
1776420274 27
1776420279 22
1776420284 22
1776420289 22
1776420294 22
1776420299 22
1776420304 22
```
</details>

---

