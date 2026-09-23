---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 05:54:12 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 14 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1790156704 48
1790156709 48
1790156714 48
1790156719 48
1790156724 47
1790156729 47
1790156734 47
1790156739 47
1790156744 47
1790156749 47
1790156754 47
1790156759 47
1790156764 47
1790156769 47
1790156774 47
1790156779 47
1790156784 48
1790156789 48
1790156794 48
1790156799 48
```
</details>

---

