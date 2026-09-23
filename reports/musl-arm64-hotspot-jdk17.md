---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 09:09:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 11 |
| Allocations | 119 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1790168671 45
1790168676 40
1790168681 40
1790168686 40
1790168691 40
1790168696 40
1790168701 40
1790168706 40
1790168711 40
1790168716 40
1790168721 40
1790168726 40
1790168731 40
1790168736 40
1790168741 45
1790168746 45
1790168751 45
1790168756 45
1790168761 45
1790168766 45
```
</details>

---

