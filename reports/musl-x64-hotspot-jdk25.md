---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 16:21:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 60-70 cores)</summary>

```
1794950073 62
1794950078 62
1794950083 62
1794950088 62
1794950093 62
1794950098 62
1794950103 62
1794950108 62
1794950113 62
1794950118 62
1794950123 62
1794950128 62
1794950133 60
1794950138 60
1794950143 60
1794950148 60
1794950153 60
1794950158 60
1794950163 60
1794950168 60
```
</details>

---

