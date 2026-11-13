---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:44:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 93 |
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
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 69-93 cores)</summary>

```
1794584434 69
1794584439 69
1794584444 69
1794584449 69
1794584454 69
1794584459 69
1794584464 69
1794584469 69
1794584474 69
1794584479 69
1794584484 69
1794584489 69
1794584494 69
1794584499 69
1794584504 69
1794584509 91
1794584514 91
1794584519 91
1794584524 91
1794584529 91
```
</details>

---

