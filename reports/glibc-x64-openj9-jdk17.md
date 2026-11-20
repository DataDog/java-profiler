---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 16:44:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 12 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 78-84 cores)</summary>

```
1795210750 78
1795210755 78
1795210760 78
1795210765 78
1795210770 78
1795210775 78
1795210780 79
1795210785 79
1795210790 79
1795210795 79
1795210800 79
1795210805 79
1795210810 79
1795210815 79
1795210820 79
1795210825 79
1795210830 79
1795210835 84
1795210840 84
1795210845 84
```
</details>

---

