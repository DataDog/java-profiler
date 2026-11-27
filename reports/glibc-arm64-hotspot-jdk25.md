---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 08:26:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 10 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (3 unique values: 42-64 cores)</summary>

```
1795785830 47
1795785835 47
1795785840 47
1795785845 47
1795785850 42
1795785855 42
1795785860 42
1795785865 42
1795785870 42
1795785875 42
1795785880 42
1795785885 42
1795785890 42
1795785895 42
1795785900 42
1795785905 42
1795785910 42
1795785915 42
1795785920 42
1795785925 42
```
</details>

---

