---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-05 06:41:09 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1791196552 25
1791196557 25
1791196562 25
1791196567 25
1791196572 27
1791196577 27
1791196582 27
1791196587 27
1791196592 27
1791196597 27
1791196602 27
1791196607 27
1791196612 27
1791196617 27
1791196622 27
1791196627 27
1791196632 27
1791196637 27
1791196642 27
1791196647 27
```
</details>

---

