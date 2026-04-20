---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 03:42:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 10 |
| Allocations | 416 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1776670539 30
1776670544 30
1776670549 30
1776670554 30
1776670559 30
1776670564 30
1776670569 30
1776670574 30
1776670579 30
1776670584 30
1776670589 30
1776670594 30
1776670599 30
1776670604 30
1776670609 30
1776670614 32
1776670619 32
1776670624 32
1776670629 32
1776670634 32
```
</details>

---

