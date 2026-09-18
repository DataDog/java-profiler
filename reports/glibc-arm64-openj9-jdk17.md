---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:13:58 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 11 |
| Allocations | 163 |

<details>
<summary>CPU Timeline (2 unique values: 41-48 cores)</summary>

```
1789743343 41
1789743348 41
1789743353 41
1789743358 41
1789743363 41
1789743368 41
1789743373 41
1789743378 41
1789743383 41
1789743388 41
1789743393 41
1789743398 48
1789743403 48
1789743408 48
1789743413 48
1789743418 48
1789743423 48
1789743428 48
1789743433 48
1789743438 48
```
</details>

---

