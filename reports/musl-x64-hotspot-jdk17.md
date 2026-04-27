---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-27 04:26:04 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (4 unique values: 23-31 cores)</summary>

```
1777277947 31
1777277952 31
1777277957 31
1777277962 31
1777277967 31
1777277972 31
1777277977 31
1777277982 31
1777277987 31
1777277992 31
1777277997 31
1777278002 31
1777278007 31
1777278012 31
1777278017 29
1777278022 29
1777278027 29
1777278032 29
1777278037 29
1777278042 31
```
</details>

---

