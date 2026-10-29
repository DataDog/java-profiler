---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 06:55:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 62-66 cores)</summary>

```
1793271000 64
1793271005 66
1793271010 66
1793271015 66
1793271020 66
1793271025 66
1793271030 66
1793271035 66
1793271040 66
1793271045 66
1793271050 66
1793271055 62
1793271060 62
1793271065 62
1793271070 62
1793271075 62
1793271080 62
1793271085 62
1793271090 62
1793271095 62
```
</details>

---

