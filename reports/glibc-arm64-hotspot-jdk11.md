---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 12:26:42 EDT

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
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 8 |
| Allocations | 317 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1792599642 48
1792599647 48
1792599652 48
1792599657 48
1792599662 48
1792599667 48
1792599672 48
1792599677 48
1792599682 48
1792599687 48
1792599692 48
1792599697 48
1792599702 40
1792599707 40
1792599712 40
1792599717 40
1792599722 40
1792599727 40
1792599732 40
1792599737 40
```
</details>

---

