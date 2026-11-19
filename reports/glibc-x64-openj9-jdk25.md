---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 09:12:32 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (6 unique values: 47-59 cores)</summary>

```
1795097287 48
1795097292 48
1795097297 48
1795097302 49
1795097307 49
1795097312 47
1795097317 47
1795097322 47
1795097327 47
1795097332 47
1795097337 54
1795097342 54
1795097347 51
1795097352 51
1795097357 51
1795097362 51
1795097367 51
1795097372 51
1795097377 51
1795097382 51
```
</details>

---

