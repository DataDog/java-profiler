---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-29 11:49:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1079 |
| Sample Rate | 17.98/sec |
| Health Score | 1124% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 32-37 cores)</summary>

```
1777477268 37
1777477273 37
1777477278 37
1777477283 37
1777477288 37
1777477293 37
1777477298 37
1777477303 37
1777477308 37
1777477313 37
1777477318 37
1777477323 37
1777477328 37
1777477333 37
1777477338 32
1777477343 32
1777477348 32
1777477353 32
1777477358 32
1777477363 32
```
</details>

---

