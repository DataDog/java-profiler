---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 08:31:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 14 |
| Allocations | 177 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795008252 51
1795008257 51
1795008262 51
1795008267 51
1795008272 51
1795008277 51
1795008282 51
1795008287 51
1795008292 51
1795008297 51
1795008302 51
1795008307 51
1795008312 51
1795008317 51
1795008322 51
1795008327 51
1795008332 51
1795008337 51
1795008342 51
1795008347 46
```
</details>

---

