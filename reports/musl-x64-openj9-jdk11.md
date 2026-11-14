---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-14 13:57:45 EST

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 8 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 74-93 cores)</summary>

```
1794682409 93
1794682414 93
1794682419 93
1794682424 93
1794682429 93
1794682434 76
1794682439 76
1794682444 76
1794682449 74
1794682454 74
1794682459 74
1794682464 74
1794682469 74
1794682474 74
1794682479 74
1794682484 74
1794682489 74
1794682494 74
1794682499 74
1794682504 74
```
</details>

---

