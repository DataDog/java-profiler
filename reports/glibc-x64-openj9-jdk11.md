---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 03:20:27 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 49-71 cores)</summary>

```
1795594577 49
1795594582 49
1795594587 49
1795594592 49
1795594597 51
1795594602 51
1795594607 51
1795594612 51
1795594617 51
1795594622 51
1795594627 51
1795594632 51
1795594637 51
1795594642 51
1795594647 49
1795594652 49
1795594657 69
1795594662 69
1795594667 69
1795594672 69
```
</details>

---

