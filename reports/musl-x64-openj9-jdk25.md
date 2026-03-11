---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-11 05:23:34 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 11 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 13 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (5 unique values: 62-81 cores)</summary>

```
1773220567 62
1773220572 62
1773220577 62
1773220582 62
1773220587 62
1773220592 62
1773220597 62
1773220602 71
1773220607 71
1773220612 71
1773220617 71
1773220622 71
1773220627 71
1773220632 71
1773220637 71
1773220642 69
1773220647 69
1773220652 69
1773220657 69
1773220662 69
```
</details>

---

