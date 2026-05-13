---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-13 09:58:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 10-15 cores)</summary>

```
1778680392 10
1778680397 10
1778680402 10
1778680407 10
1778680412 10
1778680417 10
1778680422 10
1778680427 13
1778680432 13
1778680437 11
1778680442 11
1778680447 11
1778680452 11
1778680457 11
1778680462 11
1778680467 11
1778680472 11
1778680477 11
1778680482 11
1778680487 11
```
</details>

---

