---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-27 14:14:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 19.63/sec |
| Health Score | 1227% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 892 |
| Sample Rate | 29.73/sec |
| Health Score | 1858% |
| Threads | 12 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1769540953 32
1769540958 32
1769540963 32
1769540968 32
1769540973 32
1769540978 32
1769540983 32
1769540988 32
1769540993 32
1769540998 32
1769541003 32
1769541008 32
1769541013 32
1769541018 32
1769541023 32
1769541028 32
1769541033 32
1769541038 32
1769541043 32
1769541048 32
```
</details>

---

