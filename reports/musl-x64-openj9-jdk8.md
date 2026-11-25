---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 07:51:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 50-52 cores)</summary>

```
1795610769 52
1795610774 52
1795610779 52
1795610784 52
1795610789 52
1795610794 52
1795610799 52
1795610804 52
1795610809 52
1795610814 52
1795610819 52
1795610824 52
1795610829 52
1795610834 52
1795610839 52
1795610844 52
1795610849 52
1795610854 52
1795610859 52
1795610864 50
```
</details>

---

