---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 06:41:34 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1791282946 23
1791282951 23
1791282956 23
1791282961 23
1791282966 23
1791282971 28
1791282976 28
1791282981 28
1791282986 28
1791282991 28
1791282996 28
1791283001 28
1791283006 28
1791283011 28
1791283016 28
1791283021 28
1791283026 28
1791283031 28
1791283036 28
1791283041 28
```
</details>

---

