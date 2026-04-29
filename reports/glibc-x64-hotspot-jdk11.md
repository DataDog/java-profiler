---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-29 11:49:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 836 |
| Sample Rate | 13.93/sec |
| Health Score | 871% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (5 unique values: 56-67 cores)</summary>

```
1777477268 67
1777477273 62
1777477278 62
1777477283 62
1777477288 62
1777477293 58
1777477298 58
1777477303 58
1777477308 58
1777477313 56
1777477318 56
1777477323 56
1777477328 56
1777477333 56
1777477338 58
1777477343 58
1777477348 58
1777477353 58
1777477358 58
1777477363 58
```
</details>

---

