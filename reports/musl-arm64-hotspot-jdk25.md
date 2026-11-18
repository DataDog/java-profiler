---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:34:32 EST

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
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1795015830 51
1795015835 51
1795015840 51
1795015845 51
1795015850 51
1795015855 51
1795015860 51
1795015865 51
1795015870 51
1795015875 51
1795015880 51
1795015885 64
1795015890 64
1795015895 64
1795015900 64
1795015905 64
1795015910 64
1795015915 64
1795015920 64
1795015925 64
```
</details>

---

