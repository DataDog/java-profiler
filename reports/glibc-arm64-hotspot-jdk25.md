---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 16:05:36 EST

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 11 |
| Allocations | 162 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793739729 48
1793739734 48
1793739739 48
1793739744 48
1793739749 48
1793739754 48
1793739759 48
1793739764 48
1793739769 48
1793739774 48
1793739779 48
1793739784 48
1793739789 48
1793739794 48
1793739799 48
1793739804 48
1793739809 48
1793739814 48
1793739819 48
1793739824 48
```
</details>

---

