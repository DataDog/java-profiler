---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 16:50:38 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 9 |
| Allocations | 202 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 10 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1789677732 48
1789677737 48
1789677742 48
1789677747 48
1789677752 48
1789677757 48
1789677762 48
1789677767 48
1789677772 48
1789677778 48
1789677783 48
1789677788 40
1789677793 40
1789677798 40
1789677803 40
1789677808 40
1789677813 40
1789677818 40
1789677823 40
1789677828 40
```
</details>

---

