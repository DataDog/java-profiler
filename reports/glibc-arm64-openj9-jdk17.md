---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 09:19:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 7 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794838457 45
1794838462 45
1794838467 45
1794838472 45
1794838477 45
1794838482 45
1794838487 45
1794838492 45
1794838497 45
1794838502 45
1794838507 45
1794838512 45
1794838517 45
1794838522 48
1794838527 48
1794838532 48
1794838537 48
1794838542 43
1794838547 43
1794838552 43
```
</details>

---

