---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 08:37:35 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 71-94 cores)</summary>

```
1795440786 71
1795440791 71
1795440796 71
1795440801 71
1795440806 71
1795440811 71
1795440816 71
1795440821 71
1795440826 71
1795440831 71
1795440836 71
1795440841 71
1795440846 71
1795440851 71
1795440856 71
1795440861 71
1795440866 94
1795440871 94
1795440876 94
1795440881 94
```
</details>

---

