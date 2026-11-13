---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:16:40 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 10 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 910 |
| Sample Rate | 15.17/sec |
| Health Score | 948% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 64-68 cores)</summary>

```
1794582748 68
1794582753 68
1794582758 68
1794582763 68
1794582768 68
1794582773 68
1794582778 68
1794582783 66
1794582788 66
1794582793 64
1794582798 64
1794582803 64
1794582808 64
1794582813 64
1794582818 64
1794582823 64
1794582828 64
1794582833 64
1794582838 64
1794582843 64
```
</details>

---

