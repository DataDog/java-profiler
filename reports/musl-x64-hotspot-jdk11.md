---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 16:21:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 823 |
| Sample Rate | 13.72/sec |
| Health Score | 857% |
| Threads | 10 |
| Allocations | 579 |

<details>
<summary>CPU Timeline (3 unique values: 52-73 cores)</summary>

```
1794950073 52
1794950078 52
1794950083 52
1794950088 52
1794950093 52
1794950098 52
1794950103 52
1794950108 52
1794950113 52
1794950118 52
1794950123 73
1794950128 73
1794950133 73
1794950138 73
1794950143 71
1794950148 71
1794950153 71
1794950159 71
1794950164 71
1794950169 71
```
</details>

---

