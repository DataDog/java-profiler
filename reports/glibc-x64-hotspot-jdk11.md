---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 11:38:31 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 930 |
| Sample Rate | 15.50/sec |
| Health Score | 969% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1786376024 29
1786376030 29
1786376035 29
1786376040 32
1786376045 32
1786376050 32
1786376055 32
1786376060 32
1786376065 32
1786376070 32
1786376075 32
1786376080 32
1786376085 32
1786376090 32
1786376095 32
1786376100 32
1786376105 32
1786376110 32
1786376115 32
1786376120 32
```
</details>

---

