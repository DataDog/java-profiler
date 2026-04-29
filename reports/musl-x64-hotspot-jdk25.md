---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-29 11:49:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 31-36 cores)</summary>

```
1777477248 36
1777477253 36
1777477258 36
1777477263 36
1777477268 36
1777477273 36
1777477278 36
1777477283 36
1777477288 36
1777477293 34
1777477298 34
1777477303 34
1777477308 34
1777477313 36
1777477318 36
1777477323 36
1777477328 36
1777477333 31
1777477338 31
1777477343 31
```
</details>

---

