---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-03 18:51:23 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 10 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 61-81 cores)</summary>

```
1788475512 61
1788475517 61
1788475522 61
1788475527 61
1788475532 61
1788475537 61
1788475542 61
1788475547 61
1788475552 61
1788475557 61
1788475562 61
1788475567 61
1788475572 61
1788475577 61
1788475582 81
1788475587 81
1788475592 81
1788475597 81
1788475602 81
1788475607 81
```
</details>

---

