---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-05 13:28:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 24-30 cores)</summary>

```
1772734949 28
1772734954 28
1772734959 28
1772734964 28
1772734969 24
1772734974 24
1772734979 24
1772734984 24
1772734989 24
1772734994 28
1772734999 28
1772735004 30
1772735009 30
1772735014 28
1772735019 28
1772735024 30
1772735029 30
1772735034 30
1772735039 30
1772735044 30
```
</details>

---

