---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 14:04:31 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 8 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 10 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786557616 48
1786557621 48
1786557626 48
1786557631 48
1786557636 48
1786557641 48
1786557646 48
1786557651 48
1786557656 43
1786557661 43
1786557666 43
1786557671 43
1786557676 43
1786557681 43
1786557686 43
1786557691 43
1786557696 43
1786557701 43
1786557706 43
1786557711 48
```
</details>

---

