---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-17 09:10:31 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 11 |
| Allocations | 146 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786971602 43
1786971607 43
1786971612 43
1786971617 43
1786971622 43
1786971627 43
1786971632 48
1786971637 48
1786971642 48
1786971647 48
1786971652 48
1786971657 48
1786971662 48
1786971667 48
1786971672 48
1786971677 48
1786971682 48
1786971687 48
1786971692 48
1786971697 48
```
</details>

---

