---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:23:35 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 782 |
| Sample Rate | 13.03/sec |
| Health Score | 814% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 58-67 cores)</summary>

```
1795195131 58
1795195136 58
1795195141 58
1795195146 58
1795195151 58
1795195156 58
1795195161 58
1795195166 58
1795195171 58
1795195176 67
1795195181 67
1795195186 67
1795195191 67
1795195196 67
1795195201 67
1795195206 67
1795195211 67
1795195216 67
1795195221 67
1795195226 67
```
</details>

---

