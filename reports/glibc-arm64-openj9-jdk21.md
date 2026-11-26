---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 06:11:45 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 9 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795691269 59
1795691274 59
1795691279 59
1795691284 59
1795691289 59
1795691294 59
1795691299 59
1795691304 59
1795691310 64
1795691315 64
1795691320 64
1795691325 64
1795691330 64
1795691335 64
1795691340 64
1795691345 64
1795691350 64
1795691355 64
1795691360 64
1795691365 64
```
</details>

---

