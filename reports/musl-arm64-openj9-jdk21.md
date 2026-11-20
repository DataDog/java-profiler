---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 09:56:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 11 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (4 unique values: 39-45 cores)</summary>

```
1795186303 39
1795186308 39
1795186313 45
1795186318 45
1795186323 45
1795186328 42
1795186334 42
1795186339 42
1795186344 42
1795186349 42
1795186354 42
1795186359 42
1795186364 42
1795186369 42
1795186374 42
1795186379 45
1795186384 45
1795186389 45
1795186394 45
1795186399 43
```
</details>

---

