---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 08:24:38 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 10 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (3 unique values: 55-79 cores)</summary>

```
1795785550 79
1795785555 79
1795785560 79
1795785565 79
1795785570 79
1795785575 79
1795785580 79
1795785585 79
1795785590 79
1795785595 58
1795785600 58
1795785605 58
1795785610 58
1795785615 58
1795785620 58
1795785625 55
1795785630 55
1795785635 55
1795785640 55
1795785645 55
```
</details>

---

