---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 02:36:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 12 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1790663506 48
1790663511 48
1790663516 48
1790663521 48
1790663526 48
1790663531 48
1790663536 48
1790663541 48
1790663546 48
1790663551 48
1790663556 48
1790663561 48
1790663566 46
1790663571 46
1790663576 46
1790663581 46
1790663586 46
1790663591 46
1790663596 46
1790663601 46
```
</details>

---

