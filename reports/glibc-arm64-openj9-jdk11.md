---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:50:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 11 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795632437 48
1795632442 48
1795632447 43
1795632452 43
1795632457 43
1795632462 43
1795632467 43
1795632472 43
1795632477 43
1795632482 43
1795632487 43
1795632492 43
1795632497 43
1795632502 43
1795632507 43
1795632512 43
1795632517 43
1795632522 43
1795632527 43
1795632532 43
```
</details>

---

