---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 04:46:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 50-64 cores)</summary>

```
1786437735 50
1786437740 50
1786437745 50
1786437750 50
1786437755 50
1786437760 50
1786437765 50
1786437770 50
1786437775 52
1786437780 52
1786437785 52
1786437790 52
1786437795 52
1786437800 52
1786437805 52
1786437811 52
1786437816 52
1786437821 52
1786437826 64
1786437831 64
```
</details>

---

