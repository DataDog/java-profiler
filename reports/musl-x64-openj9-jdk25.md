---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 09:57:30 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 12 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 55-59 cores)</summary>

```
1795186258 57
1795186263 57
1795186268 57
1795186273 57
1795186278 57
1795186283 57
1795186288 57
1795186293 57
1795186298 57
1795186303 57
1795186308 57
1795186313 57
1795186318 55
1795186323 55
1795186328 57
1795186333 57
1795186338 57
1795186343 57
1795186348 57
1795186353 57
```
</details>

---

