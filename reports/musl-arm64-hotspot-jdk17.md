---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 15:41:02 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 24-34 cores)</summary>

```
1795379800 34
1795379805 34
1795379810 34
1795379815 34
1795379820 34
1795379826 34
1795379831 34
1795379836 24
1795379841 24
1795379846 24
1795379851 24
1795379856 24
1795379861 24
1795379866 24
1795379871 24
1795379876 24
1795379881 24
1795379886 24
1795379891 24
1795379896 24
```
</details>

---

