---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-16 09:13:22 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 10 |
| Allocations | 133 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 30-43 cores)</summary>

```
1792156124 43
1792156129 38
1792156134 38
1792156139 30
1792156144 30
1792156149 30
1792156154 30
1792156159 30
1792156164 30
1792156169 30
1792156174 30
1792156179 30
1792156184 30
1792156189 30
1792156194 30
1792156199 30
1792156204 30
1792156209 30
1792156214 30
1792156219 30
```
</details>

---

