---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 01:04:38 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 63-64 cores)</summary>

```
1786337968 63
1786337973 64
1786337978 64
1786337983 64
1786337988 64
1786337993 64
1786337998 64
1786338003 64
1786338008 64
1786338013 64
1786338018 64
1786338023 64
1786338028 64
1786338033 64
1786338038 64
1786338043 64
1786338048 64
1786338053 64
1786338058 64
1786338063 64
```
</details>

---

