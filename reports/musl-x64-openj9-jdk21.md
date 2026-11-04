---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 12:28:14 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 74-94 cores)</summary>

```
1793812756 74
1793812761 74
1793812766 74
1793812771 74
1793812776 74
1793812781 94
1793812786 94
1793812791 94
1793812796 94
1793812801 94
1793812806 94
1793812811 94
1793812816 94
1793812821 94
1793812826 94
1793812831 88
1793812836 88
1793812841 88
1793812846 88
1793812851 88
```
</details>

---

