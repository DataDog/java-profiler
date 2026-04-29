---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-29 11:49:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (6 unique values: 71-77 cores)</summary>

```
1777477238 77
1777477243 77
1777477248 77
1777477253 77
1777477258 77
1777477263 77
1777477268 75
1777477273 75
1777477278 74
1777477283 74
1777477288 74
1777477293 74
1777477298 74
1777477303 74
1777477308 74
1777477313 76
1777477318 76
1777477323 73
1777477328 73
1777477333 73
```
</details>

---

