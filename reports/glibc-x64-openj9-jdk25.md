---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 06:56:59 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1795434764 65
1795434769 63
1795434774 63
1795434779 63
1795434784 63
1795434789 63
1795434794 63
1795434799 63
1795434804 63
1795434809 63
1795434814 63
1795434819 63
1795434824 63
1795434829 65
1795434834 65
1795434839 65
1795434844 65
1795434849 65
1795434854 65
1795434859 65
```
</details>

---

