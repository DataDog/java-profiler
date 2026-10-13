---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-13 12:35:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 21-64 cores)</summary>

```
1791908939 21
1791908944 21
1791908949 21
1791908954 21
1791908959 21
1791908964 21
1791908969 21
1791908974 21
1791908979 59
1791908984 59
1791908989 59
1791908994 64
1791908999 64
1791909004 64
1791909009 64
1791909014 64
1791909019 64
1791909024 64
1791909029 64
1791909034 64
```
</details>

---

