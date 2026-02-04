---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-04 14:09:44 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 10 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 819 |
| Sample Rate | 13.65/sec |
| Health Score | 853% |
| Threads | 12 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (5 unique values: 56-67 cores)</summary>

```
1770231798 61
1770231803 61
1770231808 61
1770231813 61
1770231818 61
1770231823 61
1770231828 61
1770231833 61
1770231838 61
1770231843 61
1770231848 61
1770231853 61
1770231858 56
1770231863 56
1770231868 56
1770231873 56
1770231878 58
1770231883 58
1770231888 58
1770231893 58
```
</details>

---

