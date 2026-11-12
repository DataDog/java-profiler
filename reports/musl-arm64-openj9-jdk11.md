---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 04:59:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 14 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1794477233 28
1794477238 28
1794477243 28
1794477248 28
1794477253 28
1794477258 28
1794477263 28
1794477268 28
1794477273 28
1794477278 28
1794477283 48
1794477288 48
1794477293 28
1794477298 28
1794477303 28
1794477308 28
1794477313 28
1794477318 28
1794477323 28
1794477328 28
```
</details>

---

