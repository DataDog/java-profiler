---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-13 03:49:54 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 276 |
| Sample Rate | 4.60/sec |
| Health Score | 287% |
| Threads | 11 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1786607130 28
1786607135 28
1786607140 28
1786607145 28
1786607150 28
1786607155 28
1786607160 28
1786607165 28
1786607170 28
1786607175 33
1786607180 33
1786607185 33
1786607190 33
1786607195 33
1786607200 33
1786607205 33
1786607210 33
1786607215 33
1786607220 33
1786607225 33
```
</details>

---

