---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-04 01:00:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1017 |
| Sample Rate | 16.95/sec |
| Health Score | 1059% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 69-81 cores)</summary>

```
1791089719 76
1791089724 81
1791089729 81
1791089734 81
1791089739 81
1791089744 81
1791089749 81
1791089754 71
1791089759 71
1791089764 71
1791089769 71
1791089774 71
1791089779 71
1791089784 71
1791089789 71
1791089794 71
1791089799 69
1791089804 69
1791089809 69
1791089814 69
```
</details>

---

