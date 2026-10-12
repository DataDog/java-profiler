---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-12 05:55:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 13-16 cores)</summary>

```
1791798700 13
1791798705 16
1791798710 16
1791798716 16
1791798721 16
1791798726 15
1791798731 15
1791798736 15
1791798741 15
1791798746 15
1791798751 15
1791798756 15
1791798761 15
1791798766 15
1791798771 15
1791798776 16
1791798781 16
1791798786 15
1791798791 15
1791798796 15
```
</details>

---

