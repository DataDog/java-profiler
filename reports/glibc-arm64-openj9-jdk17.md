---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-01-27 09:00:57 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 13 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769514262 24
1769514267 24
1769514272 24
1769514277 24
1769514282 24
1769514287 24
1769514292 24
1769514297 24
1769514302 24
1769514307 24
1769514312 24
1769514317 24
1769514322 24
1769514327 24
1769514332 24
1769514337 24
1769514342 24
1769514347 24
1769514352 24
1769514357 24
```
</details>

---

