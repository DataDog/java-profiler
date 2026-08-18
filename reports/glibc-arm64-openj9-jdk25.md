---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-18 13:40:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 8 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (4 unique values: 58-64 cores)</summary>

```
1787074522 62
1787074527 62
1787074532 62
1787074537 62
1787074542 62
1787074547 62
1787074552 62
1787074557 62
1787074562 62
1787074567 62
1787074572 62
1787074577 64
1787074582 64
1787074587 58
1787074592 58
1787074597 58
1787074603 58
1787074608 58
1787074613 58
1787074618 59
```
</details>

---

