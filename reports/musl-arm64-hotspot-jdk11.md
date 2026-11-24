---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 11:51:14 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 12 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795538741 43
1795538746 43
1795538751 43
1795538756 48
1795538761 48
1795538766 43
1795538771 43
1795538776 43
1795538781 43
1795538786 43
1795538791 43
1795538796 43
1795538801 43
1795538806 43
1795538811 43
1795538816 43
1795538821 43
1795538826 43
1795538831 43
1795538836 48
```
</details>

---

