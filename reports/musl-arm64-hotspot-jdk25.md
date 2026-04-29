---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-29 11:49:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777477253 64
1777477258 64
1777477263 64
1777477268 64
1777477273 64
1777477278 64
1777477283 64
1777477288 64
1777477293 64
1777477298 64
1777477303 64
1777477308 64
1777477313 64
1777477318 64
1777477323 64
1777477328 64
1777477333 64
1777477338 64
1777477343 64
1777477348 64
```
</details>

---

