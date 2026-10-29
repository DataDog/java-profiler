---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 07:57:22 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793274815 48
1793274820 48
1793274825 48
1793274830 48
1793274835 48
1793274840 48
1793274845 48
1793274850 48
1793274855 48
1793274860 48
1793274865 48
1793274870 48
1793274875 48
1793274880 48
1793274885 48
1793274890 48
1793274895 48
1793274900 43
1793274905 43
1793274910 43
```
</details>

---

