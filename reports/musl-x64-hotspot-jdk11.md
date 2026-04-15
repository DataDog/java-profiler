---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-15 13:00:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 73 |
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
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 59-73 cores)</summary>

```
1776272234 62
1776272239 62
1776272244 62
1776272249 62
1776272254 62
1776272259 62
1776272264 62
1776272269 62
1776272274 62
1776272279 62
1776272284 62
1776272289 62
1776272294 62
1776272299 62
1776272304 62
1776272309 62
1776272314 62
1776272319 64
1776272324 64
1776272329 64
```
</details>

---

