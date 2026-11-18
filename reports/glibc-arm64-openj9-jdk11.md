---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:06:20 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 327 |
| Sample Rate | 5.45/sec |
| Health Score | 341% |
| Threads | 14 |
| Allocations | 178 |

<details>
<summary>CPU Timeline (2 unique values: 29-30 cores)</summary>

```
1795010502 29
1795010507 29
1795010512 29
1795010517 29
1795010522 29
1795010527 29
1795010532 29
1795010537 29
1795010542 30
1795010547 30
1795010552 30
1795010557 30
1795010562 30
1795010567 30
1795010572 30
1795010577 30
1795010582 30
1795010587 30
1795010592 30
1795010597 30
```
</details>

---

