---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 12:52:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 10 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794937487 30
1794937492 30
1794937497 30
1794937502 30
1794937507 30
1794937512 30
1794937517 30
1794937522 30
1794937527 30
1794937532 30
1794937537 30
1794937542 30
1794937547 30
1794937552 30
1794937557 30
1794937562 30
1794937567 32
1794937572 32
1794937577 32
1794937582 32
```
</details>

---

