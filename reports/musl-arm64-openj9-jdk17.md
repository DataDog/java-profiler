---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-13 11:55:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 12 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786636218 48
1786636223 48
1786636228 48
1786636233 48
1786636238 48
1786636243 48
1786636248 48
1786636253 48
1786636258 48
1786636263 48
1786636268 48
1786636273 48
1786636278 43
1786636283 43
1786636288 43
1786636293 43
1786636298 43
1786636303 43
1786636308 43
1786636313 43
```
</details>

---

