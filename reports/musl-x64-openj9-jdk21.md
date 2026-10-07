---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-07 10:47:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 928 |
| Sample Rate | 15.47/sec |
| Health Score | 967% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 79-90 cores)</summary>

```
1791384024 90
1791384029 90
1791384034 90
1791384039 90
1791384044 90
1791384049 90
1791384054 90
1791384059 90
1791384064 90
1791384069 90
1791384074 90
1791384079 90
1791384084 82
1791384089 82
1791384094 82
1791384099 82
1791384104 82
1791384109 82
1791384114 82
1791384119 82
```
</details>

---

