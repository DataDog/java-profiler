---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-26 01:04:20 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
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
| Allocations | 89 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 10 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1787720257 40
1787720262 40
1787720267 40
1787720272 40
1787720277 40
1787720282 40
1787720287 40
1787720292 48
1787720297 48
1787720302 48
1787720307 48
1787720312 48
1787720317 48
1787720322 48
1787720327 48
1787720332 48
1787720337 48
1787720343 48
1787720348 48
1787720353 48
```
</details>

---

