---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-19 04:26:38 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 47-64 cores)</summary>

```
1787127667 64
1787127672 64
1787127677 64
1787127682 64
1787127687 64
1787127692 64
1787127697 64
1787127702 64
1787127707 64
1787127712 64
1787127717 64
1787127722 64
1787127727 64
1787127732 64
1787127737 64
1787127742 64
1787127747 64
1787127752 64
1787127757 52
1787127762 52
```
</details>

---

