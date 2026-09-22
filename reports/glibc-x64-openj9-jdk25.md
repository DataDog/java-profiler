---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (5 unique values: 33-68 cores)</summary>

```
1790094016 57
1790094021 57
1790094026 57
1790094031 57
1790094036 57
1790094041 57
1790094047 57
1790094052 57
1790094057 57
1790094062 68
1790094067 68
1790094072 40
1790094077 40
1790094082 40
1790094087 40
1790094092 40
1790094097 40
1790094102 40
1790094107 43
1790094112 43
```
</details>

---

