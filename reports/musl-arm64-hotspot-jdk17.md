---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:48:34 EST

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
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 9 |
| Allocations | 124 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795113777 45
1795113782 45
1795113787 45
1795113792 45
1795113797 45
1795113802 45
1795113807 45
1795113812 45
1795113817 45
1795113822 45
1795113827 45
1795113832 45
1795113837 45
1795113842 50
1795113848 50
1795113853 45
1795113858 45
1795113863 45
1795113868 45
1795113873 45
```
</details>

---

