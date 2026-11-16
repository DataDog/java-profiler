---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 09:21:40 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1794838626 43
1794838631 43
1794838636 43
1794838641 43
1794838646 43
1794838651 43
1794838656 43
1794838661 43
1794838666 43
1794838671 43
1794838676 43
1794838681 43
1794838686 43
1794838691 43
1794838696 43
1794838701 43
1794838706 43
1794838711 45
1794838716 45
1794838721 45
```
</details>

---

