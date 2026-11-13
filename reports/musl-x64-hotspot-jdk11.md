---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:15:31 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 856 |
| Sample Rate | 14.27/sec |
| Health Score | 892% |
| Threads | 11 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1794582642 82
1794582647 82
1794582652 82
1794582657 82
1794582662 82
1794582668 82
1794582673 82
1794582678 82
1794582683 80
1794582688 80
1794582693 82
1794582698 82
1794582703 82
1794582708 82
1794582713 82
1794582718 82
1794582723 82
1794582728 82
1794582733 82
1794582738 80
```
</details>

---

