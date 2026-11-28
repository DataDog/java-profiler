---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-28 05:48:05 EST

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 16-21 cores)</summary>

```
1795862646 16
1795862651 16
1795862656 16
1795862661 16
1795862666 16
1795862671 16
1795862676 16
1795862681 21
1795862686 21
1795862691 21
1795862696 21
1795862701 21
1795862706 21
1795862711 21
1795862716 21
1795862721 21
1795862726 21
1795862731 21
1795862736 21
1795862741 21
```
</details>

---

