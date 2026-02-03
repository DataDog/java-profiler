---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 08:20:47 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 13 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 42-62 cores)</summary>

```
1770124602 48
1770124607 48
1770124612 48
1770124617 48
1770124622 48
1770124627 48
1770124632 48
1770124637 62
1770124642 62
1770124647 62
1770124652 62
1770124657 62
1770124662 62
1770124667 62
1770124672 42
1770124677 42
1770124682 42
1770124687 42
1770124692 42
1770124697 42
```
</details>

---

