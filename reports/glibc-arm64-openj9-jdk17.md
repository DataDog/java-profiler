---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:16:16 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795691240 64
1795691245 64
1795691250 64
1795691255 64
1795691260 64
1795691265 64
1795691270 64
1795691275 64
1795691280 59
1795691285 59
1795691290 59
1795691295 59
1795691300 59
1795691305 59
1795691310 59
1795691315 59
1795691320 59
1795691325 59
1795691330 59
1795691335 59
```
</details>

---

