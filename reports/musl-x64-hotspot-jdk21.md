---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 08:24:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 11 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 26-51 cores)</summary>

```
1795785555 26
1795785560 26
1795785565 26
1795785570 26
1795785575 26
1795785580 26
1795785585 26
1795785590 26
1795785595 26
1795785600 43
1795785605 43
1795785610 51
1795785615 51
1795785620 51
1795785625 51
1795785630 51
1795785635 51
1795785640 51
1795785645 51
1795785650 51
```
</details>

---

