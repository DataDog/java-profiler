---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 11:38:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1786376050 44
1786376055 44
1786376060 44
1786376065 44
1786376070 44
1786376075 44
1786376080 44
1786376085 44
1786376090 44
1786376095 44
1786376100 44
1786376105 44
1786376110 44
1786376115 44
1786376120 44
1786376125 44
1786376130 44
1786376135 44
1786376140 39
1786376145 39
```
</details>

---

