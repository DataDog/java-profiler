---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 06:57:00 EST

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
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 45-50 cores)</summary>

```
1795434745 48
1795434750 48
1795434755 50
1795434760 50
1795434765 50
1795434770 50
1795434775 50
1795434780 50
1795434785 50
1795434790 50
1795434795 50
1795434800 50
1795434805 50
1795434810 50
1795434815 50
1795434821 50
1795434826 50
1795434831 50
1795434836 45
1795434841 45
```
</details>

---

