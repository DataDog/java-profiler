---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 08:48:17 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 13 |
| Allocations | 169 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793277851 30
1793277856 30
1793277862 30
1793277867 30
1793277872 30
1793277877 30
1793277882 30
1793277887 30
1793277892 30
1793277897 30
1793277902 30
1793277907 30
1793277912 30
1793277917 30
1793277922 30
1793277927 30
1793277932 30
1793277937 30
1793277942 30
1793277947 30
```
</details>

---

