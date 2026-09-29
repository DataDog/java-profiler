---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 03:05:52 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 244 |
| Sample Rate | 4.07/sec |
| Health Score | 254% |
| Threads | 11 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1790665317 44
1790665322 64
1790665327 64
1790665332 64
1790665337 64
1790665342 64
1790665347 64
1790665352 64
1790665357 64
1790665362 64
1790665367 64
1790665372 64
1790665377 64
1790665382 64
1790665387 64
1790665392 64
1790665397 64
1790665402 64
1790665407 64
1790665412 64
```
</details>

---

