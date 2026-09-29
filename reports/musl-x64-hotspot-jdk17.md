---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-29 00:59:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1790657708 94
1790657713 94
1790657718 94
1790657723 92
1790657728 92
1790657733 92
1790657738 92
1790657743 92
1790657748 92
1790657753 94
1790657758 94
1790657764 94
1790657769 94
1790657774 94
1790657779 94
1790657784 94
1790657789 94
1790657794 94
1790657799 94
1790657804 94
```
</details>

---

