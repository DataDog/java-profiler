---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 17:43:38 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790026701 43
1790026706 48
1790026711 48
1790026716 48
1790026721 48
1790026726 48
1790026731 48
1790026736 48
1790026741 48
1790026746 48
1790026751 48
1790026756 48
1790026761 48
1790026766 48
1790026771 48
1790026776 48
1790026781 48
1790026786 48
1790026791 48
1790026796 48
```
</details>

---

