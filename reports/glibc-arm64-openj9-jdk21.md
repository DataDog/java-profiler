---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 05:04:13 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (5 unique values: 29-37 cores)</summary>

```
1793178009 31
1793178015 31
1793178020 31
1793178025 29
1793178030 29
1793178035 29
1793178040 29
1793178045 33
1793178050 33
1793178055 32
1793178060 32
1793178065 32
1793178070 32
1793178075 32
1793178080 32
1793178085 32
1793178090 37
1793178095 37
1793178100 37
1793178105 37
```
</details>

---

