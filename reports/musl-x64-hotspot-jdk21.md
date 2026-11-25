---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 07:51:10 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 75-78 cores)</summary>

```
1795610744 78
1795610749 78
1795610754 78
1795610759 78
1795610764 78
1795610769 78
1795610774 78
1795610779 78
1795610784 78
1795610789 78
1795610794 76
1795610799 76
1795610804 76
1795610809 76
1795610814 76
1795610819 77
1795610824 77
1795610829 77
1795610834 77
1795610839 77
```
</details>

---

