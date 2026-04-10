---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-10 02:47:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (7 unique values: 42-68 cores)</summary>

```
1775803403 68
1775803408 68
1775803413 68
1775803418 68
1775803423 68
1775803428 63
1775803433 63
1775803438 63
1775803443 63
1775803448 48
1775803453 48
1775803458 48
1775803463 45
1775803468 45
1775803473 45
1775803478 45
1775803483 45
1775803488 45
1775803493 50
1775803498 50
```
</details>

---

