---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-06 06:41:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 15 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 41-52 cores)</summary>

```
1791282951 41
1791282956 41
1791282961 41
1791282966 41
1791282971 41
1791282976 41
1791282981 41
1791282986 41
1791282991 41
1791282996 41
1791283001 41
1791283006 41
1791283011 41
1791283016 41
1791283021 52
1791283026 52
1791283031 52
1791283036 52
1791283041 52
1791283046 52
```
</details>

---

