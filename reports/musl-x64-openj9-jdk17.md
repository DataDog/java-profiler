---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-11-20 12:12:26 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (1 unique values: 94-94 cores)</summary>

```
1795194412 94
1795194417 94
1795194422 94
1795194427 94
1795194432 94
1795194437 94
1795194442 94
1795194447 94
1795194452 94
1795194457 94
1795194462 94
1795194467 94
1795194472 94
1795194477 94
1795194482 94
1795194487 94
1795194492 94
1795194497 94
1795194502 94
1795194507 94
```
</details>

---

