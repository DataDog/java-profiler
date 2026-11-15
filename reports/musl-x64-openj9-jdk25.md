---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-15 18:02:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1794783525 44
1794783531 44
1794783536 44
1794783541 46
1794783546 46
1794783551 46
1794783556 46
1794783561 46
1794783566 46
1794783571 46
1794783576 46
1794783581 46
1794783586 46
1794783591 46
1794783596 46
1794783601 44
1794783606 44
1794783611 44
1794783616 44
1794783621 44
```
</details>

---

