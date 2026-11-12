---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:01:29 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 10 |
| Allocations | 559 |

<details>
<summary>CPU Timeline (4 unique values: 90-96 cores)</summary>

```
1794477253 90
1794477258 90
1794477263 90
1794477268 90
1794477273 90
1794477278 90
1794477283 90
1794477288 90
1794477293 90
1794477298 90
1794477303 90
1794477308 90
1794477313 90
1794477318 90
1794477323 90
1794477328 90
1794477333 90
1794477338 92
1794477343 92
1794477348 92
```
</details>

---

