---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-22 11:31:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (5 unique values: 35-53 cores)</summary>

```
1776871163 35
1776871168 35
1776871173 35
1776871178 35
1776871183 35
1776871188 35
1776871193 35
1776871198 39
1776871203 39
1776871208 43
1776871213 43
1776871218 43
1776871223 43
1776871228 43
1776871233 43
1776871238 43
1776871243 48
1776871248 48
1776871253 53
1776871258 53
```
</details>

---

