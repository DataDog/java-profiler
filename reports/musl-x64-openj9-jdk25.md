---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-13 05:44:22 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 10 |
| Allocations | 437 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 13 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 27-33 cores)</summary>

```
1773394713 29
1773394718 29
1773394723 29
1773394728 29
1773394733 29
1773394738 29
1773394743 29
1773394748 29
1773394753 29
1773394758 29
1773394763 29
1773394768 33
1773394773 33
1773394778 27
1773394783 27
1773394788 27
1773394793 27
1773394798 27
1773394803 32
1773394808 32
```
</details>

---

