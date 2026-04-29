---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 11:49:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 44-50 cores)</summary>

```
1777477248 44
1777477253 46
1777477258 46
1777477263 46
1777477268 46
1777477273 46
1777477278 46
1777477283 46
1777477288 46
1777477293 46
1777477298 46
1777477303 46
1777477308 46
1777477313 46
1777477318 46
1777477323 46
1777477328 50
1777477333 50
1777477338 50
1777477343 50
```
</details>

---

