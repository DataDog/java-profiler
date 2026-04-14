---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-14 04:48:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 326 |
| Sample Rate | 5.43/sec |
| Health Score | 339% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 40-64 cores)</summary>

```
1776156207 64
1776156212 64
1776156217 64
1776156222 64
1776156227 64
1776156232 64
1776156237 64
1776156242 64
1776156247 64
1776156252 64
1776156257 64
1776156262 64
1776156267 64
1776156272 64
1776156277 64
1776156282 64
1776156287 64
1776156292 64
1776156297 64
1776156302 40
```
</details>

---

