---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-21 09:40:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 32-46 cores)</summary>

```
1789997723 46
1789997728 46
1789997733 46
1789997738 46
1789997743 46
1789997748 46
1789997753 32
1789997758 32
1789997763 32
1789997768 32
1789997773 32
1789997779 32
1789997784 32
1789997789 32
1789997794 32
1789997799 32
1789997804 32
1789997809 32
1789997814 32
1789997819 37
```
</details>

---

