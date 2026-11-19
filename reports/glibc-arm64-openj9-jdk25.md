---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:48:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 13 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (3 unique values: 43-50 cores)</summary>

```
1795113810 43
1795113815 43
1795113820 43
1795113825 43
1795113830 43
1795113835 43
1795113840 43
1795113845 43
1795113850 43
1795113855 43
1795113860 43
1795113865 43
1795113870 43
1795113875 43
1795113880 43
1795113885 43
1795113890 43
1795113895 43
1795113900 43
1795113905 45
```
</details>

---

