---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 05:59:41 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 82-91 cores)</summary>

```
1793876042 91
1793876047 91
1793876052 91
1793876057 91
1793876062 91
1793876067 91
1793876072 91
1793876077 82
1793876082 82
1793876087 82
1793876092 82
1793876097 82
1793876102 82
1793876107 82
1793876112 82
1793876117 82
1793876122 82
1793876127 82
1793876132 82
1793876137 82
```
</details>

---

