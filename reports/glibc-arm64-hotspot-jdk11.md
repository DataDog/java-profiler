---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 09:21:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794838626 48
1794838631 48
1794838636 48
1794838641 48
1794838646 48
1794838651 48
1794838656 48
1794838661 48
1794838666 48
1794838671 48
1794838676 48
1794838681 48
1794838686 48
1794838691 48
1794838696 48
1794838701 43
1794838706 43
1794838711 43
1794838716 43
1794838721 38
```
</details>

---

