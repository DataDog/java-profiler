---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 13:02:35 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 13.25/sec |
| Health Score | 828% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (5 unique values: 39-51 cores)</summary>

```
1778086642 43
1778086647 43
1778086652 43
1778086657 43
1778086662 43
1778086667 43
1778086672 43
1778086677 39
1778086682 39
1778086687 39
1778086692 39
1778086697 39
1778086702 39
1778086707 39
1778086712 39
1778086717 42
1778086722 42
1778086727 46
1778086732 46
1778086737 46
```
</details>

---

