---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 11:31:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 244 |
| Sample Rate | 4.07/sec |
| Health Score | 254% |
| Threads | 10 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 802 |
| Sample Rate | 13.37/sec |
| Health Score | 836% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795105592 45
1795105597 45
1795105602 45
1795105607 45
1795105612 45
1795105617 45
1795105622 45
1795105627 45
1795105632 45
1795105637 45
1795105642 45
1795105647 50
1795105652 50
1795105657 50
1795105662 50
1795105667 50
1795105672 50
1795105677 45
1795105682 45
1795105687 45
```
</details>

---

