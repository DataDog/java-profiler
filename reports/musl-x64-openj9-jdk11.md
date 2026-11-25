---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:00:32 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 42 |
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
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 19-42 cores)</summary>

```
1795618554 19
1795618559 19
1795618564 19
1795618569 19
1795618574 19
1795618579 19
1795618584 19
1795618589 19
1795618594 19
1795618599 19
1795618604 19
1795618609 19
1795618614 19
1795618619 23
1795618624 23
1795618629 23
1795618634 23
1795618639 23
1795618644 23
1795618649 42
```
</details>

---

