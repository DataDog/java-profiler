---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:31:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1794572819 51
1794572824 51
1794572829 51
1794572834 51
1794572839 51
1794572844 51
1794572849 51
1794572854 51
1794572859 51
1794572864 51
1794572869 51
1794572874 51
1794572879 51
1794572884 51
1794572889 51
1794572894 51
1794572899 51
1794572904 51
1794572909 49
1794572914 49
```
</details>

---

