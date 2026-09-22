---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 15:04:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (4 unique values: 13-23 cores)</summary>

```
1790103626 18
1790103631 18
1790103636 23
1790103641 23
1790103646 16
1790103651 16
1790103656 16
1790103661 16
1790103666 16
1790103671 16
1790103676 16
1790103681 16
1790103686 13
1790103691 13
1790103696 13
1790103701 13
1790103706 13
1790103711 13
1790103716 13
1790103721 13
```
</details>

---

