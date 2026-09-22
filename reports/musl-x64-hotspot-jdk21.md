---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 09:50:45 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 46-58 cores)</summary>

```
1790084781 48
1790084786 48
1790084791 48
1790084796 48
1790084801 48
1790084806 46
1790084811 46
1790084816 46
1790084821 46
1790084826 46
1790084831 46
1790084836 46
1790084841 46
1790084846 46
1790084851 46
1790084856 56
1790084861 56
1790084866 56
1790084871 56
1790084876 56
```
</details>

---

