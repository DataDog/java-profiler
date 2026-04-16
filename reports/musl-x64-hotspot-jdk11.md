---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-16 06:24:11 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1102 |
| Sample Rate | 18.37/sec |
| Health Score | 1148% |
| Threads | 12 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 55-75 cores)</summary>

```
1776334687 55
1776334692 55
1776334697 55
1776334702 55
1776334707 55
1776334712 55
1776334717 55
1776334722 55
1776334727 55
1776334732 55
1776334737 55
1776334742 55
1776334747 75
1776334752 75
1776334757 72
1776334762 72
1776334767 72
1776334772 72
1776334777 72
1776334782 72
```
</details>

---

