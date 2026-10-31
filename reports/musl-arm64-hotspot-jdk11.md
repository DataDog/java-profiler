---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-31 06:53:48 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 11 |
| Allocations | 212 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1793443750 46
1793443755 46
1793443761 46
1793443766 48
1793443771 48
1793443776 48
1793443781 48
1793443786 48
1793443791 48
1793443796 48
1793443801 48
1793443806 43
1793443811 43
1793443816 43
1793443821 43
1793443826 43
1793443831 43
1793443836 43
1793443841 43
1793443846 41
```
</details>

---

