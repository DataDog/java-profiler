---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-10 02:47:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (7 unique values: 42-68 cores)</summary>

```
1775803407 68
1775803412 68
1775803417 68
1775803422 68
1775803427 68
1775803432 63
1775803437 63
1775803442 63
1775803447 63
1775803452 48
1775803457 48
1775803462 45
1775803467 45
1775803472 45
1775803477 45
1775803482 45
1775803487 45
1775803492 50
1775803497 50
1775803502 50
```
</details>

---

