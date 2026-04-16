---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-16 06:24:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 871 |
| Sample Rate | 14.52/sec |
| Health Score | 907% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 89-93 cores)</summary>

```
1776334537 93
1776334542 93
1776334548 93
1776334553 93
1776334558 93
1776334563 93
1776334568 93
1776334573 93
1776334578 93
1776334583 93
1776334588 93
1776334593 93
1776334598 89
1776334603 89
1776334608 89
1776334613 89
1776334618 89
1776334623 89
1776334628 89
1776334633 89
```
</details>

---

