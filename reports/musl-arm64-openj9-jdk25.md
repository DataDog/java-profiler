---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 09:21:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 33 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 37-45 cores)</summary>

```
1794838630 45
1794838635 45
1794838640 45
1794838645 40
1794838650 40
1794838655 40
1794838661 40
1794838666 40
1794838671 40
1794838676 40
1794838681 40
1794838686 40
1794838691 40
1794838696 40
1794838701 40
1794838706 40
1794838711 40
1794838716 40
1794838721 40
1794838726 37
```
</details>

---

