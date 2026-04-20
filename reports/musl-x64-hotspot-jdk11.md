---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 09:29:36 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (7 unique values: 50-87 cores)</summary>

```
1776691499 54
1776691504 54
1776691509 50
1776691514 50
1776691519 50
1776691524 50
1776691529 50
1776691534 50
1776691539 54
1776691544 54
1776691549 54
1776691554 54
1776691559 54
1776691564 54
1776691569 54
1776691574 53
1776691579 53
1776691584 75
1776691589 75
1776691594 75
```
</details>

---

