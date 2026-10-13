---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-13 12:35:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791908949 51
1791908954 51
1791908959 51
1791908964 51
1791908969 51
1791908974 51
1791908979 51
1791908984 51
1791908989 51
1791908994 51
1791908999 51
1791909004 51
1791909009 51
1791909014 51
1791909019 51
1791909024 51
1791909029 51
1791909034 51
1791909039 51
1791909044 51
```
</details>

---

