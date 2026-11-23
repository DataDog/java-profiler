---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:59:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1795452899 44
1795452904 44
1795452909 44
1795452914 44
1795452919 44
1795452924 44
1795452929 44
1795452934 44
1795452939 44
1795452944 44
1795452949 44
1795452954 44
1795452959 44
1795452964 44
1795452969 44
1795452974 44
1795452979 44
1795452984 44
1795452989 49
1795452994 49
```
</details>

---

