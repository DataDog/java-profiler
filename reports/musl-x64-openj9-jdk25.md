---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-05 20:41:46 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 12 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1770341693 26
1770341698 26
1770341703 26
1770341708 26
1770341713 26
1770341718 26
1770341723 26
1770341728 26
1770341733 26
1770341738 26
1770341743 26
1770341748 26
1770341753 30
1770341758 30
1770341763 30
1770341768 30
1770341773 30
1770341778 30
1770341783 30
1770341788 30
```
</details>

---

