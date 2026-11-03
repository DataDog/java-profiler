---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 12:55:04 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 9 |
| Allocations | 586 |

<details>
<summary>CPU Timeline (4 unique values: 54-59 cores)</summary>

```
1793728203 55
1793728208 55
1793728213 55
1793728218 55
1793728223 55
1793728228 55
1793728233 55
1793728238 57
1793728243 57
1793728248 57
1793728253 57
1793728258 57
1793728263 57
1793728268 57
1793728273 57
1793728278 57
1793728283 57
1793728288 57
1793728293 57
1793728298 57
```
</details>

---

