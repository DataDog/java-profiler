---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 15:26:49 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787080986 64
1787080991 64
1787080996 64
1787081001 64
1787081006 64
1787081011 64
1787081016 64
1787081021 64
1787081026 64
1787081031 64
1787081036 64
1787081041 64
1787081046 64
1787081051 64
1787081056 64
1787081061 64
1787081066 64
1787081071 64
1787081076 64
1787081081 64
```
</details>

---

