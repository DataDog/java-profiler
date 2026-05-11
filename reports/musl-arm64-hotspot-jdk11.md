---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 11:23:13 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778512701 64
1778512706 64
1778512711 64
1778512716 64
1778512721 64
1778512726 64
1778512731 64
1778512736 64
1778512741 64
1778512746 64
1778512751 64
1778512756 64
1778512761 64
1778512766 64
1778512771 64
1778512776 64
1778512781 64
1778512786 64
1778512791 64
1778512796 64
```
</details>

---

