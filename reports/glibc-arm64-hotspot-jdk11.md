---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:31:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (5 unique values: 47-64 cores)</summary>

```
1789737695 58
1789737700 59
1789737705 59
1789737710 59
1789737715 64
1789737720 64
1789737725 64
1789737730 64
1789737735 64
1789737740 64
1789737745 64
1789737751 64
1789737756 64
1789737761 64
1789737766 64
1789737771 64
1789737776 64
1789737781 64
1789737786 50
1789737791 50
```
</details>

---

