---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 11:12:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 10 |
| Allocations | 133 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 13 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (4 unique values: 43-64 cores)</summary>

```
1794931698 43
1794931703 43
1794931708 43
1794931713 47
1794931718 47
1794931723 47
1794931728 47
1794931733 51
1794931738 51
1794931743 51
1794931748 51
1794931753 51
1794931758 51
1794931763 51
1794931768 51
1794931773 51
1794931778 51
1794931783 51
1794931788 51
1794931793 51
```
</details>

---

