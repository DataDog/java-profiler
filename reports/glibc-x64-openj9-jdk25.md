---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 13:10:30 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 47-55 cores)</summary>

```
1790096774 47
1790096779 47
1790096784 47
1790096789 47
1790096794 47
1790096799 47
1790096804 47
1790096809 47
1790096814 47
1790096819 47
1790096824 47
1790096829 47
1790096834 47
1790096839 47
1790096844 47
1790096849 47
1790096854 47
1790096859 47
1790096864 47
1790096869 47
```
</details>

---

