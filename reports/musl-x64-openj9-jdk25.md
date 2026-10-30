---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 06:28:18 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793355786 48
1793355791 48
1793355796 48
1793355801 48
1793355806 48
1793355811 48
1793355816 48
1793355821 48
1793355826 48
1793355831 48
1793355836 46
1793355841 46
1793355846 46
1793355851 46
1793355856 46
1793355861 46
1793355866 46
1793355871 46
1793355876 46
1793355881 46
```
</details>

---

