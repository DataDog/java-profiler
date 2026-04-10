---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-10 13:20:14 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 14 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1775841327 48
1775841332 48
1775841337 48
1775841342 48
1775841347 48
1775841352 48
1775841357 48
1775841362 48
1775841367 48
1775841372 48
1775841377 48
1775841382 48
1775841387 48
1775841392 48
1775841397 48
1775841402 48
1775841407 48
1775841412 48
1775841417 48
1775841422 48
```
</details>

---

