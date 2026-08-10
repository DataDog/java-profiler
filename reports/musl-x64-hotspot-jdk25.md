---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-09 21:22:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1786324649 62
1786324654 62
1786324659 62
1786324664 62
1786324669 62
1786324674 62
1786324679 62
1786324684 62
1786324689 62
1786324694 62
1786324699 62
1786324704 60
1786324709 60
1786324714 60
1786324719 60
1786324724 60
1786324729 60
1786324734 60
1786324739 60
1786324744 62
```
</details>

---

