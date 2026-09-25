---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 14:37:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 14 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790361208 50
1790361213 50
1790361218 50
1790361223 50
1790361228 50
1790361233 50
1790361238 50
1790361243 50
1790361248 50
1790361253 50
1790361258 50
1790361263 50
1790361268 50
1790361274 50
1790361279 50
1790361284 50
1790361289 50
1790361294 50
1790361299 50
1790361304 50
```
</details>

---

