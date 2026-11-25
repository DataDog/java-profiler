---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 05:53:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (4 unique values: 37-64 cores)</summary>

```
1795603796 37
1795603801 37
1795603806 37
1795603811 37
1795603816 37
1795603821 37
1795603826 37
1795603831 42
1795603836 42
1795603841 47
1795603846 47
1795603851 47
1795603856 47
1795603861 47
1795603866 47
1795603871 47
1795603876 47
1795603881 47
1795603886 64
1795603891 64
```
</details>

---

