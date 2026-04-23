---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-23 14:32:13 EDT

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1776968755 62
1776968760 62
1776968765 62
1776968770 62
1776968775 62
1776968780 64
1776968785 64
1776968790 64
1776968795 64
1776968800 64
1776968805 64
1776968810 64
1776968815 64
1776968820 64
1776968825 64
1776968830 64
1776968835 64
1776968840 64
1776968845 64
1776968850 64
```
</details>

---

