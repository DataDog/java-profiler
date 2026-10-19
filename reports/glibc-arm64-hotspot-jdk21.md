---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-18 21:26:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1792372860 46
1792372865 46
1792372870 46
1792372875 46
1792372880 46
1792372885 46
1792372890 46
1792372895 46
1792372900 46
1792372905 48
1792372910 48
1792372915 48
1792372920 48
1792372925 48
1792372930 48
1792372935 48
1792372940 48
1792372945 48
1792372950 48
1792372955 48
```
</details>

---

