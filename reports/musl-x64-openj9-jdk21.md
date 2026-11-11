---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 16:06:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (5 unique values: 75-92 cores)</summary>

```
1794430806 75
1794430811 75
1794430816 75
1794430821 75
1794430826 77
1794430831 77
1794430836 77
1794430841 77
1794430846 77
1794430851 77
1794430856 77
1794430861 77
1794430866 91
1794430871 91
1794430876 89
1794430881 89
1794430886 89
1794430891 92
1794430896 92
1794430901 92
```
</details>

---

