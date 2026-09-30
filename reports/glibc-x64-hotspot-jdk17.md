---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-30 08:24:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 9 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 46-49 cores)</summary>

```
1790770750 46
1790770755 46
1790770760 46
1790770765 46
1790770770 46
1790770775 46
1790770780 46
1790770785 46
1790770790 46
1790770795 46
1790770800 46
1790770805 46
1790770810 46
1790770815 46
1790770820 46
1790770825 46
1790770830 46
1790770835 49
1790770840 49
1790770845 49
```
</details>

---

