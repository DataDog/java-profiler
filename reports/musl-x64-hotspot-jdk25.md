---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:52:59 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 76-93 cores)</summary>

```
1795614480 79
1795614485 79
1795614490 79
1795614495 79
1795614500 79
1795614505 79
1795614510 79
1795614515 79
1795614520 79
1795614525 79
1795614530 79
1795614535 79
1795614540 79
1795614545 79
1795614550 79
1795614555 79
1795614561 76
1795614566 76
1795614571 76
1795614576 76
```
</details>

---

