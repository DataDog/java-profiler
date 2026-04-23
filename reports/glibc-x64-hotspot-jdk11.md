---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 13:55:55 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 876 |
| Sample Rate | 14.60/sec |
| Health Score | 912% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 23-28 cores)</summary>

```
1776966671 23
1776966676 23
1776966681 23
1776966686 23
1776966691 23
1776966696 26
1776966701 26
1776966706 28
1776966711 28
1776966716 28
1776966721 28
1776966726 28
1776966731 28
1776966736 28
1776966741 28
1776966746 28
1776966751 28
1776966756 28
1776966761 28
1776966766 28
```
</details>

---

