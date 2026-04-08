---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-08 12:51:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1128 |
| Sample Rate | 18.80/sec |
| Health Score | 1175% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 24-28 cores)</summary>

```
1775666689 28
1775666694 28
1775666699 28
1775666704 28
1775666709 28
1775666714 26
1775666719 26
1775666724 26
1775666729 26
1775666734 26
1775666739 26
1775666744 26
1775666749 26
1775666754 26
1775666759 26
1775666764 26
1775666769 24
1775666774 24
1775666779 24
1775666784 24
```
</details>

---

