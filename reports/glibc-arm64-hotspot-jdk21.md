---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 14:09:03 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 11 |
| Allocations | 182 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 15 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1795028661 45
1795028666 45
1795028671 45
1795028676 45
1795028681 45
1795028686 45
1795028691 45
1795028696 45
1795028701 45
1795028706 45
1795028711 45
1795028716 45
1795028721 45
1795028726 43
1795028731 43
1795028736 43
1795028741 43
1795028746 43
1795028751 43
1795028756 43
```
</details>

---

