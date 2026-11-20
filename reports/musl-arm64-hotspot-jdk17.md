---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:39:28 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 15 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 35-50 cores)</summary>

```
1795196082 35
1795196087 35
1795196092 35
1795196097 50
1795196102 50
1795196107 50
1795196112 48
1795196117 48
1795196122 48
1795196127 48
1795196132 48
1795196137 48
1795196142 48
1795196147 48
1795196152 48
1795196157 48
1795196162 48
1795196167 48
1795196172 48
1795196177 48
```
</details>

---

