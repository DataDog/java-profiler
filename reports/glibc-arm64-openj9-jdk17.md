---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-18 15:28:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 11 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1787080940 14
1787080945 14
1787080950 14
1787080955 14
1787080960 14
1787080965 14
1787080970 14
1787080975 14
1787080980 14
1787080985 14
1787080990 14
1787080995 14
1787081000 14
1787081005 14
1787081010 14
1787081015 34
1787081020 34
1787081025 34
1787081030 34
1787081035 34
```
</details>

---

