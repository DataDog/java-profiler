---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-17 06:07:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776420236 64
1776420241 64
1776420246 64
1776420251 64
1776420256 64
1776420261 64
1776420266 64
1776420271 64
1776420276 64
1776420281 64
1776420286 64
1776420291 64
1776420296 64
1776420301 64
1776420306 64
1776420311 64
1776420316 64
1776420321 64
1776420326 64
1776420331 64
```
</details>

---

