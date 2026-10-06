---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-06 09:30:45 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (4 unique values: 74-79 cores)</summary>

```
1791293038 76
1791293043 76
1791293048 76
1791293053 76
1791293058 76
1791293063 76
1791293068 76
1791293073 76
1791293078 76
1791293083 76
1791293088 76
1791293093 76
1791293098 74
1791293103 74
1791293108 79
1791293113 79
1791293118 79
1791293123 77
1791293128 77
1791293133 77
```
</details>

---

