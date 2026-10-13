---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-13 12:35:47 EDT

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
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 32-37 cores)</summary>

```
1791908934 32
1791908939 32
1791908944 32
1791908949 32
1791908954 32
1791908959 32
1791908964 37
1791908969 37
1791908974 37
1791908979 37
1791908984 37
1791908989 37
1791908994 37
1791908999 37
1791909004 37
1791909009 37
1791909014 37
1791909019 37
1791909024 37
1791909029 37
```
</details>

---

