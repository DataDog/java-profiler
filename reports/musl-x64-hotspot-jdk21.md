---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 11:12:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 68-76 cores)</summary>

```
1794931688 68
1794931693 68
1794931698 68
1794931703 68
1794931708 71
1794931713 71
1794931718 71
1794931723 71
1794931728 71
1794931733 71
1794931738 71
1794931743 71
1794931748 71
1794931753 71
1794931758 71
1794931763 73
1794931768 73
1794931773 73
1794931778 73
1794931783 73
```
</details>

---

