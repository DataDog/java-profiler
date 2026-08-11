---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 20:17:25 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 89 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (3 unique values: 22-56 cores)</summary>

```
1786407114 22
1786407119 22
1786407124 22
1786407129 22
1786407134 22
1786407139 22
1786407144 22
1786407149 22
1786407154 22
1786407159 22
1786407164 22
1786407169 22
1786407174 22
1786407179 22
1786407184 22
1786407189 56
1786407194 56
1786407199 56
1786407204 56
1786407209 56
```
</details>

---

