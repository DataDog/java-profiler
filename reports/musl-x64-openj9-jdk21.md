---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-07 17:27:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 815 |
| Sample Rate | 13.58/sec |
| Health Score | 849% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 79-87 cores)</summary>

```
1791408152 83
1791408157 83
1791408162 83
1791408167 83
1791408172 83
1791408177 81
1791408182 81
1791408187 83
1791408192 83
1791408197 85
1791408202 85
1791408207 85
1791408212 85
1791408217 85
1791408222 85
1791408227 85
1791408232 85
1791408237 85
1791408242 85
1791408247 85
```
</details>

---

