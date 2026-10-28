---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-27 20:59:13 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1793148894 27
1793148899 27
1793148904 27
1793148910 27
1793148915 27
1793148920 27
1793148925 27
1793148930 27
1793148935 27
1793148940 27
1793148945 27
1793148950 27
1793148955 27
1793148960 27
1793148965 27
1793148970 27
1793148975 27
1793148980 27
1793148985 25
1793148990 25
```
</details>

---

