---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-05 06:41:09 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 427 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1791196566 25
1791196571 27
1791196576 27
1791196581 27
1791196586 27
1791196591 27
1791196596 27
1791196601 27
1791196606 27
1791196611 27
1791196616 27
1791196621 27
1791196626 27
1791196631 27
1791196636 27
1791196641 27
1791196646 27
1791196651 27
1791196656 27
1791196661 27
```
</details>

---

