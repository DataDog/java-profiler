---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-11 11:40:59 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (3 unique values: 56-60 cores)</summary>

```
1770827497 60
1770827502 60
1770827507 60
1770827512 60
1770827517 60
1770827522 60
1770827527 60
1770827532 60
1770827537 60
1770827542 56
1770827547 56
1770827552 56
1770827557 56
1770827562 56
1770827567 56
1770827572 56
1770827577 56
1770827582 56
1770827587 56
1770827592 56
```
</details>

---

