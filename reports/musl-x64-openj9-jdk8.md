---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-12 07:55:51 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 365 |
| Sample Rate | 6.08/sec |
| Health Score | 380% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 52-77 cores)</summary>

```
1794487794 60
1794487799 60
1794487804 60
1794487809 60
1794487814 60
1794487819 60
1794487824 60
1794487829 60
1794487834 60
1794487839 60
1794487844 60
1794487849 60
1794487854 60
1794487859 52
1794487864 52
1794487869 52
1794487874 52
1794487879 52
1794487884 52
1794487889 52
```
</details>

---

