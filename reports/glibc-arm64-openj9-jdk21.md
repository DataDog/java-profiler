---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:50:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (4 unique values: 42-64 cores)</summary>

```
1795632447 47
1795632452 47
1795632457 47
1795632462 42
1795632467 42
1795632472 42
1795632477 42
1795632482 42
1795632487 42
1795632492 42
1795632497 42
1795632502 42
1795632507 59
1795632512 59
1795632517 59
1795632522 59
1795632527 59
1795632532 59
1795632537 59
1795632542 59
```
</details>

---

