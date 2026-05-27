---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-27 06:39:48 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 23-43 cores)</summary>

```
1779878181 23
1779878186 23
1779878191 42
1779878196 42
1779878201 42
1779878206 42
1779878211 42
1779878216 42
1779878221 42
1779878226 43
1779878231 43
1779878236 43
1779878241 43
1779878246 43
1779878251 43
1779878256 43
1779878261 43
1779878266 43
1779878271 43
1779878276 43
```
</details>

---

