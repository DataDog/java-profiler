---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 09:40:57 EDT

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 7-9 cores)</summary>

```
1789997708 9
1789997713 9
1789997718 9
1789997723 9
1789997728 7
1789997733 7
1789997738 7
1789997743 7
1789997748 7
1789997753 7
1789997758 7
1789997763 7
1789997768 7
1789997773 7
1789997778 9
1789997783 9
1789997788 7
1789997793 7
1789997798 7
1789997803 7
```
</details>

---

