---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 11:38:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 9 |
| Allocations | 92 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 13 |
| Allocations | 90 |

<details>
<summary>CPU Timeline (3 unique values: 36-44 cores)</summary>

```
1786376030 36
1786376035 36
1786376040 36
1786376045 36
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
```
</details>

---

