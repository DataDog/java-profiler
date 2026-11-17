---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 11:12:48 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 15 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 36-46 cores)</summary>

```
1794931698 46
1794931703 46
1794931708 46
1794931713 46
1794931718 46
1794931723 46
1794931728 46
1794931733 46
1794931738 46
1794931743 46
1794931748 46
1794931753 46
1794931758 36
1794931763 36
1794931768 36
1794931773 36
1794931778 36
1794931783 36
1794931788 36
1794931793 36
```
</details>

---

