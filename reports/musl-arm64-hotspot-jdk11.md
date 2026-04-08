---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-08 12:50:59 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 164 |
| Sample Rate | 2.73/sec |
| Health Score | 171% |
| Threads | 10 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1775666666 64
1775666671 64
1775666676 64
1775666681 64
1775666686 64
1775666691 64
1775666696 64
1775666701 64
1775666706 64
1775666711 64
1775666716 64
1775666721 64
1775666726 64
1775666731 64
1775666736 64
1775666741 64
1775666746 64
1775666751 64
1775666756 64
1775666761 64
```
</details>

---

