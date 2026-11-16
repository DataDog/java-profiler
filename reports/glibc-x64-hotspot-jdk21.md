---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 05:31:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 67-91 cores)</summary>

```
1794824819 69
1794824824 69
1794824829 69
1794824834 69
1794824839 69
1794824844 69
1794824849 69
1794824854 67
1794824859 67
1794824864 67
1794824869 69
1794824874 69
1794824879 69
1794824884 69
1794824889 69
1794824894 69
1794824899 71
1794824904 71
1794824909 71
1794824914 71
```
</details>

---

