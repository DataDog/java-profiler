---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 11:28:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1795796659 16
1795796664 16
1795796669 16
1795796674 16
1795796679 16
1795796684 16
1795796689 16
1795796694 16
1795796699 16
1795796704 16
1795796709 16
1795796714 16
1795796719 16
1795796724 16
1795796729 16
1795796734 16
1795796739 16
1795796744 16
1795796749 16
1795796754 16
```
</details>

---

