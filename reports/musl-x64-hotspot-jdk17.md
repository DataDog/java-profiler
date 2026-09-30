---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-30 07:18:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 38-60 cores)</summary>

```
1790766811 54
1790766816 54
1790766821 38
1790766826 38
1790766831 40
1790766836 40
1790766841 40
1790766846 40
1790766851 40
1790766856 40
1790766861 40
1790766866 40
1790766871 40
1790766876 40
1790766881 40
1790766886 60
1790766891 60
1790766896 60
1790766901 60
1790766906 60
```
</details>

---

