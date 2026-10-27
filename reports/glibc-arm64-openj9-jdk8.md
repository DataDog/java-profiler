---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-27 15:45:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 35 |
| Sample Rate | 0.58/sec |
| Health Score | 36% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 28-51 cores)</summary>

```
1793130002 28
1793130007 28
1793130012 28
1793130017 28
1793130022 28
1793130027 28
1793130032 51
1793130037 51
1793130042 51
1793130047 51
1793130052 51
1793130057 51
1793130062 51
1793130067 51
1793130072 51
1793130077 51
1793130082 51
1793130087 51
1793130092 51
1793130097 51
```
</details>

---

