---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:38:21 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 75 |

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
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1795001636 51
1795001641 51
1795001646 51
1795001651 51
1795001656 51
1795001661 51
1795001666 51
1795001671 51
1795001676 51
1795001681 51
1795001686 64
1795001691 64
1795001696 64
1795001701 64
1795001706 64
1795001711 64
1795001716 64
1795001721 64
1795001726 64
1795001731 64
```
</details>

---

