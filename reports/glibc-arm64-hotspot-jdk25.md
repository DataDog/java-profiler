---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-01-29 07:01:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 4.73/sec |
| Health Score | 296% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 22 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769687627 24
1769687632 24
1769687637 24
1769687642 24
1769687647 24
1769687652 24
1769687657 24
1769687662 24
1769687667 24
1769687672 24
1769687677 24
1769687682 24
1769687687 24
1769687692 24
1769687697 24
1769687702 24
1769687707 24
1769687712 24
1769687717 24
1769687722 24
```
</details>

---

