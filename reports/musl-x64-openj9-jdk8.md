---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-07 12:41:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 40-55 cores)</summary>

```
1778171846 40
1778171851 40
1778171856 40
1778171861 40
1778171866 40
1778171871 40
1778171876 50
1778171881 50
1778171886 50
1778171891 50
1778171896 50
1778171901 50
1778171906 50
1778171911 50
1778171916 50
1778171921 50
1778171926 50
1778171931 55
1778171936 55
1778171941 55
```
</details>

---

