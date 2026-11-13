---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:03:40 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 960 |
| Sample Rate | 16.00/sec |
| Health Score | 1000% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1794567532 55
1794567537 55
1794567542 55
1794567547 55
1794567552 55
1794567557 55
1794567562 55
1794567567 55
1794567572 55
1794567577 55
1794567582 55
1794567587 55
1794567592 55
1794567598 55
1794567603 55
1794567608 53
1794567613 53
1794567618 53
1794567623 53
1794567628 53
```
</details>

---

