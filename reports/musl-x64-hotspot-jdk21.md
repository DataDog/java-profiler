---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 10:44:37 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 20-26 cores)</summary>

```
1790087766 20
1790087771 20
1790087776 20
1790087781 20
1790087786 20
1790087791 20
1790087796 20
1790087801 20
1790087806 20
1790087811 20
1790087816 20
1790087821 21
1790087826 21
1790087831 21
1790087836 21
1790087841 21
1790087846 21
1790087851 21
1790087856 21
1790087861 21
```
</details>

---

