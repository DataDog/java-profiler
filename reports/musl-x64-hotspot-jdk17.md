---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-23 09:28:40 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1075 |
| Sample Rate | 17.92/sec |
| Health Score | 1120% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 41-45 cores)</summary>

```
1776950587 42
1776950592 42
1776950598 42
1776950603 42
1776950608 42
1776950613 42
1776950618 42
1776950623 44
1776950628 44
1776950633 44
1776950638 44
1776950643 44
1776950648 44
1776950653 44
1776950658 44
1776950663 44
1776950668 44
1776950673 44
1776950678 45
1776950683 45
```
</details>

---

