---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 19:06:01 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 10 |
| Allocations | 120 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1792710128 29
1792710133 29
1792710138 29
1792710143 29
1792710148 29
1792710153 29
1792710158 29
1792710163 29
1792710168 29
1792710173 29
1792710178 29
1792710183 34
1792710188 34
1792710193 34
1792710198 34
1792710203 34
1792710208 34
1792710213 34
1792710218 34
1792710223 34
```
</details>

---

