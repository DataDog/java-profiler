---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 09:19:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 434 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 10 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (5 unique values: 65-90 cores)</summary>

```
1794838487 66
1794838492 66
1794838497 66
1794838502 66
1794838507 66
1794838512 66
1794838517 68
1794838522 68
1794838527 65
1794838532 65
1794838537 65
1794838542 65
1794838547 65
1794838552 65
1794838557 65
1794838562 65
1794838567 70
1794838572 70
1794838577 70
1794838582 70
```
</details>

---

