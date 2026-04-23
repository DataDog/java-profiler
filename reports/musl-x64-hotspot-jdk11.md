---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 18:00:40 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 23-28 cores)</summary>

```
1776981408 23
1776981413 23
1776981418 23
1776981423 23
1776981428 23
1776981433 23
1776981438 28
1776981443 28
1776981448 28
1776981453 28
1776981458 28
1776981463 28
1776981468 28
1776981473 28
1776981478 26
1776981483 26
1776981488 26
1776981493 26
1776981498 28
1776981503 28
```
</details>

---

