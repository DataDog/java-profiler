---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 04:44:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1154 |
| Sample Rate | 19.23/sec |
| Health Score | 1202% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1789979833 64
1789979838 64
1789979843 64
1789979848 64
1789979853 64
1789979858 64
1789979863 62
1789979868 62
1789979873 62
1789979878 62
1789979883 62
1789979888 62
1789979893 64
1789979898 64
1789979903 64
1789979908 64
1789979913 64
1789979918 64
1789979923 64
1789979928 64
```
</details>

---

