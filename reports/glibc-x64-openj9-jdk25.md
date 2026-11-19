---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 09:13:59 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 59-72 cores)</summary>

```
1795097267 59
1795097272 59
1795097277 59
1795097282 61
1795097287 61
1795097292 61
1795097297 61
1795097302 61
1795097307 61
1795097312 61
1795097317 67
1795097322 67
1795097327 67
1795097332 67
1795097337 72
1795097342 72
1795097347 72
1795097352 72
1795097357 72
1795097362 72
```
</details>

---

