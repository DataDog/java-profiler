---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:29:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 42-52 cores)</summary>

```
1789737746 52
1789737751 52
1789737756 52
1789737761 52
1789737766 52
1789737771 52
1789737776 52
1789737781 52
1789737786 52
1789737791 52
1789737796 52
1789737801 52
1789737806 52
1789737811 52
1789737816 52
1789737821 42
1789737826 42
1789737831 42
1789737836 42
1789737841 42
```
</details>

---

