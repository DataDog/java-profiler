---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 11:12:51 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 940 |
| Sample Rate | 15.67/sec |
| Health Score | 979% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 68-76 cores)</summary>

```
1794931701 68
1794931706 71
1794931711 71
1794931716 71
1794931721 71
1794931726 71
1794931731 71
1794931736 71
1794931741 71
1794931746 71
1794931751 71
1794931756 71
1794931761 73
1794931766 73
1794931771 73
1794931776 73
1794931781 73
1794931786 73
1794931791 76
1794931796 76
```
</details>

---

