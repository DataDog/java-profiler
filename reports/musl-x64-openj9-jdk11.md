---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:13:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 9 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (3 unique values: 65-70 cores)</summary>

```
1795529227 65
1795529232 65
1795529237 65
1795529242 65
1795529247 65
1795529252 65
1795529257 65
1795529262 65
1795529267 65
1795529272 68
1795529277 68
1795529282 68
1795529287 68
1795529292 68
1795529297 68
1795529302 68
1795529307 68
1795529312 68
1795529317 68
1795529322 68
```
</details>

---

