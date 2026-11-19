---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 05:58:28 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 10 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 27-39 cores)</summary>

```
1795085621 27
1795085626 27
1795085631 27
1795085636 27
1795085641 27
1795085646 39
1795085651 39
1795085656 39
1795085661 39
1795085666 39
1795085671 39
1795085676 39
1795085681 39
1795085686 39
1795085691 39
1795085696 39
1795085701 39
1795085706 39
1795085711 39
1795085716 39
```
</details>

---

