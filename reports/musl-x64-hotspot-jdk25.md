---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-14 04:48:37 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 18-30 cores)</summary>

```
1776156191 18
1776156196 18
1776156201 18
1776156206 28
1776156211 28
1776156216 28
1776156221 28
1776156226 28
1776156231 28
1776156236 28
1776156241 30
1776156246 30
1776156251 30
1776156256 30
1776156261 30
1776156266 30
1776156271 30
1776156276 30
1776156281 30
1776156286 30
```
</details>

---

