---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-06 04:52:00 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 934 |
| Sample Rate | 15.57/sec |
| Health Score | 973% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786006051 48
1786006056 48
1786006061 48
1786006066 48
1786006071 48
1786006076 48
1786006081 48
1786006086 43
1786006091 43
1786006096 43
1786006101 43
1786006106 43
1786006111 43
1786006116 43
1786006121 43
1786006126 43
1786006131 43
1786006136 43
1786006141 43
1786006146 43
```
</details>

---

