---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 09:29:36 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1776691506 31
1776691511 31
1776691516 31
1776691521 32
1776691526 32
1776691531 32
1776691536 32
1776691541 32
1776691546 32
1776691551 32
1776691556 32
1776691561 32
1776691566 32
1776691571 32
1776691576 32
1776691581 32
1776691586 32
1776691591 32
1776691596 32
1776691601 32
```
</details>

---

