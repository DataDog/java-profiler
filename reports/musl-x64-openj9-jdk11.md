---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 17:52:28 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 985 |
| Sample Rate | 16.42/sec |
| Health Score | 1026% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1792532781 89
1792532786 89
1792532791 89
1792532796 89
1792532801 89
1792532806 89
1792532811 89
1792532816 89
1792532821 89
1792532826 89
1792532831 89
1792532836 91
1792532841 91
1792532846 91
1792532851 91
1792532856 91
1792532861 91
1792532866 91
1792532871 91
1792532876 91
```
</details>

---

