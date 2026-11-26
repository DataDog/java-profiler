---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 07:11:26 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 88-90 cores)</summary>

```
1795694841 88
1795694846 88
1795694851 88
1795694856 88
1795694861 88
1795694866 88
1795694871 88
1795694876 88
1795694881 88
1795694886 88
1795694891 88
1795694896 88
1795694901 90
1795694906 90
1795694911 90
1795694916 90
1795694921 90
1795694926 90
1795694931 90
1795694936 90
```
</details>

---

