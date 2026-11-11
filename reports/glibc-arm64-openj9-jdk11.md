---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 16:54:44 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 15 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 22-34 cores)</summary>

```
1794433771 34
1794433776 34
1794433781 34
1794433786 34
1794433791 22
1794433796 22
1794433801 22
1794433806 22
1794433811 22
1794433816 22
1794433821 22
1794433826 22
1794433831 22
1794433836 22
1794433841 22
1794433846 22
1794433851 22
1794433856 22
1794433861 22
1794433866 22
```
</details>

---

