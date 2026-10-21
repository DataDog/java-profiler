---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-21 16:37:00 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 83-91 cores)</summary>

```
1792614693 91
1792614698 91
1792614703 91
1792614708 91
1792614713 91
1792614718 91
1792614723 91
1792614728 91
1792614733 91
1792614738 91
1792614743 91
1792614748 91
1792614753 91
1792614758 91
1792614763 83
1792614768 83
1792614773 83
1792614778 83
1792614783 83
1792614788 83
```
</details>

---

