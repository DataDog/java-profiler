---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-25 11:03:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 22-34 cores)</summary>

```
1787669834 22
1787669839 22
1787669844 30
1787669849 30
1787669854 30
1787669859 30
1787669864 30
1787669869 30
1787669874 30
1787669879 30
1787669884 30
1787669889 30
1787669894 34
1787669899 34
1787669904 34
1787669909 34
1787669914 34
1787669919 34
1787669924 34
1787669929 34
```
</details>

---

