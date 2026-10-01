---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-01 07:50:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 270 |
| Sample Rate | 4.50/sec |
| Health Score | 281% |
| Threads | 12 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (2 unique values: 20-48 cores)</summary>

```
1790855158 20
1790855163 20
1790855168 20
1790855173 20
1790855178 20
1790855183 20
1790855188 20
1790855193 20
1790855198 20
1790855203 20
1790855208 20
1790855213 20
1790855218 20
1790855223 20
1790855228 20
1790855233 20
1790855238 20
1790855243 20
1790855248 20
1790855253 20
```
</details>

---

