---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-05 20:41:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 12 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 38-96 cores)</summary>

```
1770341708 94
1770341713 94
1770341718 94
1770341723 96
1770341728 96
1770341733 96
1770341738 96
1770341743 96
1770341748 96
1770341753 96
1770341758 96
1770341763 96
1770341768 96
1770341773 96
1770341778 96
1770341783 96
1770341788 96
1770341793 38
1770341798 38
1770341803 38
```
</details>

---

