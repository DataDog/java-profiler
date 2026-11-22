---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-22 15:36:13 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 63-66 cores)</summary>

```
1795379492 64
1795379497 64
1795379502 64
1795379507 64
1795379512 64
1795379517 64
1795379522 64
1795379527 64
1795379532 64
1795379537 64
1795379542 64
1795379547 64
1795379552 64
1795379557 64
1795379562 64
1795379567 64
1795379572 66
1795379577 66
1795379582 66
1795379587 66
```
</details>

---

