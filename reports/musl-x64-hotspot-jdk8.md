---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-22 11:31:59 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 68-77 cores)</summary>

```
1776871168 68
1776871173 68
1776871178 68
1776871183 70
1776871188 70
1776871193 70
1776871198 70
1776871203 70
1776871208 70
1776871213 70
1776871218 70
1776871223 70
1776871228 70
1776871233 70
1776871238 75
1776871243 75
1776871248 75
1776871253 75
1776871258 75
1776871263 75
```
</details>

---

