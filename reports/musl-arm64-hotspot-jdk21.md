---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-25 08:26:18 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 13 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1790338707 44
1790338712 44
1790338717 44
1790338722 44
1790338727 44
1790338732 44
1790338737 44
1790338742 44
1790338747 44
1790338752 48
1790338757 48
1790338762 48
1790338767 48
1790338772 48
1790338777 48
1790338782 48
1790338787 48
1790338792 48
1790338797 48
1790338802 48
```
</details>

---

