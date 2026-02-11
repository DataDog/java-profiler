---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-11 11:40:58 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 12 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 70-72 cores)</summary>

```
1770827815 72
1770827820 72
1770827825 72
1770827830 72
1770827835 72
1770827840 70
1770827845 70
1770827850 72
1770827855 72
1770827860 72
1770827865 72
1770827870 72
1770827875 72
1770827880 72
1770827885 72
1770827890 71
1770827895 71
1770827900 71
1770827905 72
1770827910 72
```
</details>

---

