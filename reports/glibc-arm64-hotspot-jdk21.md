---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 09:06:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790168592 46
1790168597 46
1790168602 46
1790168607 46
1790168612 48
1790168617 48
1790168622 48
1790168627 48
1790168632 48
1790168637 48
1790168642 48
1790168647 48
1790168652 48
1790168657 48
1790168662 48
1790168667 48
1790168672 48
1790168677 43
1790168682 43
1790168687 43
```
</details>

---

