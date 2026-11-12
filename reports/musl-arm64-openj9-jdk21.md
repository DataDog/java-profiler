---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 07:55:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1794487769 39
1794487774 39
1794487779 39
1794487784 39
1794487789 39
1794487794 39
1794487799 39
1794487804 39
1794487809 39
1794487814 39
1794487819 39
1794487824 39
1794487829 39
1794487834 44
1794487839 44
1794487844 44
1794487849 44
1794487854 44
1794487859 44
1794487864 44
```
</details>

---

