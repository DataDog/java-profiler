---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 11:46:10 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (4 unique values: 85-91 cores)</summary>

```
1791560305 89
1791560310 89
1791560315 91
1791560321 91
1791560326 91
1791560331 91
1791560336 91
1791560341 91
1791560346 89
1791560351 89
1791560356 87
1791560361 87
1791560366 87
1791560371 85
1791560376 85
1791560381 85
1791560386 85
1791560391 85
1791560396 85
1791560401 87
```
</details>

---

