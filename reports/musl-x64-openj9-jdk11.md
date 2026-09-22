---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 07:06:13 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 26-36 cores)</summary>

```
1790074841 26
1790074846 26
1790074851 26
1790074856 36
1790074861 36
1790074866 36
1790074871 36
1790074876 36
1790074881 36
1790074886 36
1790074891 36
1790074896 36
1790074901 28
1790074906 28
1790074911 28
1790074916 28
1790074921 28
1790074926 28
1790074931 28
1790074936 28
```
</details>

---

