---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 08:36:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 10 |
| Allocations | 152 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 14 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1791462745 51
1791462750 51
1791462755 56
1791462760 56
1791462765 56
1791462770 56
1791462775 56
1791462780 56
1791462785 56
1791462790 56
1791462795 56
1791462800 56
1791462805 56
1791462810 56
1791462815 56
1791462820 56
1791462825 56
1791462830 56
1791462835 56
1791462840 56
```
</details>

---

