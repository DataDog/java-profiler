---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 15:26:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 86-94 cores)</summary>

```
1787080971 94
1787080976 94
1787080981 94
1787080986 94
1787080991 92
1787080996 92
1787081001 92
1787081006 92
1787081011 94
1787081016 94
1787081021 94
1787081026 94
1787081031 94
1787081036 94
1787081041 94
1787081046 94
1787081051 94
1787081056 94
1787081061 94
1787081066 94
```
</details>

---

