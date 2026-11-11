---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:47:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 73-93 cores)</summary>

```
1794408157 73
1794408162 73
1794408167 73
1794408172 73
1794408177 73
1794408182 73
1794408187 73
1794408192 73
1794408197 73
1794408202 73
1794408207 73
1794408212 73
1794408217 73
1794408222 73
1794408227 73
1794408232 73
1794408237 73
1794408242 93
1794408247 93
1794408252 93
```
</details>

---

