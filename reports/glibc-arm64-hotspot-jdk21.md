---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 03:36:29 EDT

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 34 |
| Sample Rate | 0.57/sec |
| Health Score | 36% |
| Threads | 11 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1790580781 64
1790580786 64
1790580791 64
1790580796 64
1790580801 64
1790580806 64
1790580811 64
1790580816 64
1790580821 64
1790580826 64
1790580831 64
1790580836 64
1790580841 64
1790580846 64
1790580851 64
1790580856 64
1790580861 64
1790580866 64
1790580871 64
1790580876 64
```
</details>

---

