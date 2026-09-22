---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 13:10:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1790096695 44
1790096700 44
1790096705 44
1790096710 49
1790096715 49
1790096720 49
1790096725 49
1790096730 49
1790096735 49
1790096740 49
1790096745 49
1790096750 49
1790096755 49
1790096760 49
1790096765 49
1790096770 49
1790096775 49
1790096780 49
1790096785 49
1790096790 49
```
</details>

---

