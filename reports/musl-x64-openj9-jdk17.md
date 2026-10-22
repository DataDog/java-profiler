---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 01:13:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 8 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 24-32 cores)</summary>

```
1792645446 32
1792645451 32
1792645456 32
1792645461 32
1792645466 32
1792645471 32
1792645476 32
1792645481 32
1792645486 32
1792645491 32
1792645496 32
1792645501 32
1792645506 32
1792645511 32
1792645516 24
1792645521 24
1792645526 24
1792645531 24
1792645536 24
1792645541 24
```
</details>

---

