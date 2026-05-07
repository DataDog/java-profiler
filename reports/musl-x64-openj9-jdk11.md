---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 12:53:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 828 |
| Sample Rate | 13.80/sec |
| Health Score | 862% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 39-45 cores)</summary>

```
1778172487 39
1778172492 39
1778172497 39
1778172502 39
1778172507 39
1778172512 44
1778172517 44
1778172522 43
1778172527 43
1778172532 44
1778172537 44
1778172542 44
1778172547 44
1778172552 44
1778172557 44
1778172562 45
1778172567 45
1778172572 45
1778172577 45
1778172582 45
```
</details>

---

