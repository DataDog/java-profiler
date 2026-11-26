---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 07:11:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 22-27 cores)</summary>

```
1795694854 24
1795694859 24
1795694864 24
1795694869 24
1795694874 24
1795694879 24
1795694884 24
1795694889 24
1795694894 24
1795694899 24
1795694904 24
1795694909 24
1795694914 24
1795694919 24
1795694924 24
1795694929 22
1795694934 22
1795694939 22
1795694944 22
1795694949 22
```
</details>

---

