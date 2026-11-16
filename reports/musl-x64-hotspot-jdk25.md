---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 11:44:38 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (4 unique values: 84-92 cores)</summary>

```
1794847092 92
1794847097 92
1794847102 92
1794847107 90
1794847112 90
1794847117 90
1794847122 90
1794847127 90
1794847132 90
1794847137 90
1794847142 90
1794847147 90
1794847152 86
1794847157 86
1794847162 86
1794847167 84
1794847172 84
1794847177 84
1794847182 84
1794847187 84
```
</details>

---

