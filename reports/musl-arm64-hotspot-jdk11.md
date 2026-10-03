---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-03 04:34:57 EDT

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
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (4 unique values: 42-54 cores)</summary>

```
1791016220 44
1791016225 44
1791016230 42
1791016236 42
1791016241 42
1791016246 42
1791016251 42
1791016256 42
1791016261 47
1791016266 47
1791016271 47
1791016276 47
1791016281 54
1791016286 54
1791016291 54
1791016296 54
1791016301 54
1791016306 54
1791016311 54
1791016316 54
```
</details>

---

