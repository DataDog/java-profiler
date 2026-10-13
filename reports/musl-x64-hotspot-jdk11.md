---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-13 12:35:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1015 |
| Sample Rate | 16.92/sec |
| Health Score | 1058% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1791908929 86
1791908934 86
1791908939 86
1791908944 86
1791908949 86
1791908954 86
1791908959 86
1791908964 86
1791908969 86
1791908974 86
1791908979 86
1791908984 86
1791908989 86
1791908994 86
1791908999 84
1791909004 84
1791909009 84
1791909015 84
1791909020 84
1791909025 86
```
</details>

---

