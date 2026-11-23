---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-23 06:57:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 76-84 cores)</summary>

```
1795434708 84
1795434713 84
1795434718 84
1795434723 84
1795434728 84
1795434733 84
1795434738 84
1795434743 84
1795434748 84
1795434753 84
1795434758 84
1795434763 76
1795434768 76
1795434773 76
1795434778 79
1795434783 79
1795434788 79
1795434793 79
1795434798 79
1795434803 79
```
</details>

---

