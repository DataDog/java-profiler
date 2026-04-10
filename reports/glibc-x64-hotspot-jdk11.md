---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-10 02:47:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 63-67 cores)</summary>

```
1775803426 63
1775803431 63
1775803436 63
1775803441 63
1775803446 63
1775803451 67
1775803456 67
1775803461 67
1775803466 67
1775803471 67
1775803476 67
1775803481 65
1775803486 65
1775803491 65
1775803496 65
1775803501 65
1775803506 65
1775803511 65
1775803516 65
1775803521 65
```
</details>

---

