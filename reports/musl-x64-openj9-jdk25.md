---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:29:13 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (3 unique values: 79-83 cores)</summary>

```
1795627410 79
1795627415 79
1795627420 79
1795627425 79
1795627430 79
1795627435 79
1795627440 79
1795627445 79
1795627450 79
1795627455 83
1795627460 83
1795627465 83
1795627470 83
1795627475 83
1795627480 83
1795627485 83
1795627490 83
1795627495 83
1795627500 83
1795627505 83
```
</details>

---

