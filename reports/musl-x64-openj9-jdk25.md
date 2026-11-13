---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:15:31 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 62-69 cores)</summary>

```
1794582642 62
1794582647 69
1794582652 69
1794582657 69
1794582662 69
1794582667 69
1794582672 69
1794582677 69
1794582682 69
1794582687 69
1794582692 69
1794582697 69
1794582702 69
1794582707 69
1794582712 69
1794582717 67
1794582722 67
1794582727 67
1794582732 67
1794582737 67
```
</details>

---

