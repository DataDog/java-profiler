---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:42:11 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 894 |
| Sample Rate | 14.90/sec |
| Health Score | 931% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1789673537 96
1789673542 96
1789673547 96
1789673552 96
1789673557 96
1789673562 96
1789673567 96
1789673572 96
1789673577 96
1789673582 96
1789673587 96
1789673592 94
1789673597 94
1789673602 94
1789673607 94
1789673612 94
1789673617 96
1789673622 96
1789673627 96
1789673632 96
```
</details>

---

