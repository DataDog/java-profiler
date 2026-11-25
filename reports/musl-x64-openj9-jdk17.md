---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:29:13 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 10 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1795627412 72
1795627417 72
1795627422 72
1795627427 72
1795627432 72
1795627437 72
1795627442 72
1795627447 72
1795627452 72
1795627457 72
1795627462 72
1795627467 72
1795627472 74
1795627477 74
1795627482 74
1795627487 74
1795627492 74
1795627497 74
1795627502 74
1795627507 74
```
</details>

---

