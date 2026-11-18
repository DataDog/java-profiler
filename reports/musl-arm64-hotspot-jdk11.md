---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:34:24 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 11 |
| Allocations | 30 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795011921 64
1795011926 64
1795011931 64
1795011936 64
1795011941 64
1795011946 64
1795011951 64
1795011956 64
1795011961 64
1795011966 64
1795011971 64
1795011976 64
1795011981 64
1795011986 64
1795011991 64
1795011996 64
1795012001 64
1795012006 64
1795012011 64
1795012016 64
```
</details>

---

