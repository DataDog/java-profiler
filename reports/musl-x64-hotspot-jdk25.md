---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 17:43:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 62-72 cores)</summary>

```
1790026691 62
1790026696 62
1790026701 62
1790026706 62
1790026711 62
1790026716 72
1790026721 72
1790026726 72
1790026731 72
1790026736 72
1790026741 72
1790026746 72
1790026751 72
1790026756 72
1790026761 72
1790026766 72
1790026771 72
1790026776 72
1790026781 72
1790026786 72
```
</details>

---

