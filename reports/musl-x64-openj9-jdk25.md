---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 07:11:26 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 8 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 75-87 cores)</summary>

```
1795694831 87
1795694836 87
1795694841 87
1795694846 87
1795694851 87
1795694856 84
1795694861 84
1795694866 84
1795694871 84
1795694876 84
1795694881 84
1795694886 84
1795694891 84
1795694896 84
1795694901 84
1795694906 84
1795694911 84
1795694916 84
1795694921 84
1795694926 84
```
</details>

---

