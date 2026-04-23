---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-23 15:03:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 13 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776970691 64
1776970696 64
1776970701 64
1776970706 64
1776970711 64
1776970716 64
1776970721 64
1776970726 64
1776970731 64
1776970736 64
1776970741 64
1776970746 64
1776970751 64
1776970756 64
1776970761 64
1776970766 64
1776970771 64
1776970776 64
1776970781 64
1776970786 64
```
</details>

---

