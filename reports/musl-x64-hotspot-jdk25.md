---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-27 13:40:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 19.60/sec |
| Health Score | 1225% |
| Threads | 10 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1022 |
| Sample Rate | 34.07/sec |
| Health Score | 2129% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769538865 30
1769538870 30
1769538875 30
1769538880 30
1769538886 30
1769538891 30
1769538896 30
1769538901 30
1769538906 30
1769538911 30
1769538916 30
1769538921 30
1769538926 30
1769538931 30
1769538936 30
1769538941 32
1769538946 32
1769538951 32
1769538956 32
1769538961 30
```
</details>

---

