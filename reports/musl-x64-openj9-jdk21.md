---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 13:55:21 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 839 |
| Sample Rate | 13.98/sec |
| Health Score | 874% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1795027774 47
1795027779 47
1795027784 49
1795027789 49
1795027794 49
1795027799 51
1795027804 51
1795027809 51
1795027814 51
1795027819 51
1795027824 51
1795027829 51
1795027834 51
1795027839 51
1795027844 51
1795027849 51
1795027854 51
1795027859 51
1795027864 51
1795027869 51
```
</details>

---

