---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 15:55:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 34-40 cores)</summary>

```
1795380693 34
1795380698 34
1795380704 34
1795380709 34
1795380714 34
1795380719 36
1795380724 36
1795380729 36
1795380734 36
1795380739 36
1795380744 36
1795380749 36
1795380754 36
1795380759 38
1795380764 38
1795380769 40
1795380774 40
1795380779 40
1795380784 40
1795380789 40
```
</details>

---

