---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-15 18:26:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1794784890 94
1794784895 94
1794784900 94
1794784905 94
1794784910 96
1794784915 96
1794784920 96
1794784925 96
1794784930 94
1794784935 94
1794784940 94
1794784945 94
1794784950 94
1794784955 94
1794784960 94
1794784965 94
1794784970 94
1794784975 94
1794784980 94
1794784985 94
```
</details>

---

