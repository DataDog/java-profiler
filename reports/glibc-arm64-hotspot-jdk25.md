---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 11:44:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794588055 51
1794588060 46
1794588065 46
1794588070 46
1794588075 46
1794588080 46
1794588085 46
1794588090 46
1794588095 46
1794588100 46
1794588105 46
1794588110 46
1794588115 46
1794588120 46
1794588125 46
1794588130 46
1794588135 51
1794588140 51
1794588145 51
1794588151 51
```
</details>

---

