---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-12 13:12:34 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1770919638 30
1770919643 30
1770919648 30
1770919653 30
1770919658 30
1770919663 30
1770919668 30
1770919673 30
1770919678 30
1770919683 30
1770919688 30
1770919693 30
1770919698 30
1770919703 30
1770919708 30
1770919713 28
1770919718 28
1770919723 28
1770919728 28
1770919733 28
```
</details>

---

